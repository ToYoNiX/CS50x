import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    invested = 0
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?;", session["user_id"])
    for row in stocks:
        stock = lookup(row["symbol"])
        row["price"] = stock["price"]
        total = row["price"] * row["shares"]
        row["total"] = usd(total)
        invested += total

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    return render_template("index.html", stocks=stocks, cash=usd(cash), total=usd(cash + invested))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")

    symbols = {}
    rows = db.execute("SELECT symbol FROM stocks WHERE user_id = ?;", session["user_id"])
    for row in rows:
        symbols[row["symbol"]] = 1

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    stock, shares_str = request.form.get("symbol"), request.form.get("shares")
    stock = lookup(stock)

    if stock == None:
        return apology("INVALID SYMBOL")

    # Validate that shares is an integer and positive
    try:
        shares = int(shares_str)
        if shares < 1:
            return apology("INVALID SHARES NUMBER")
    except ValueError:
        return apology("SHARES MUST BE A POSITIVE INTEGER")

    if stock["price"] * shares > cash:
        return apology("CAN'T AFFORD")

    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - stock["price"] * shares, session["user_id"])

    if stock["symbol"] in symbols:
        shares = db.execute("SELECT shares FROM stocks WHERE symbol = ? AND user_id = ?",
                            stock["symbol"], session["user_id"])[0]["shares"] + shares
        db.execute("UPDATE stocks SET shares = ? WHERE symbol = ? AND user_id = ?;", shares, stock["symbol"], session["user_id"])
    else:
        db.execute("INSERT INTO stocks (user_id, symbol, shares) VALUES(?, ?, ?)", session["user_id"], stock["symbol"], shares)

    # History
    now = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
    db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted) VALUES(?, ?, ?, ?, ?);",
               session["user_id"], stock["symbol"], shares, stock["price"], now)

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    actions = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", history=actions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")

    symbol = lookup(request.form.get("symbol"))

    if symbol == None:
        return apology("INVALID SYMBOL!")

    return render_template("share.html", share=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username")
    password = request.form.get("password")
    confirm_password = request.form.get("confirmation")

    if password != confirm_password:
        return apology("PASSWARDS DON'T MATCH")

    users = db.execute("SELECT * FROM users WHERE username = ?;", username)
    if len(users) > 0:
        return apology("USERNAME IS USED")

    id = db.execute("SELECT COUNT(*) AS n FROM users;")[0]["n"] + 1

    if not username or not password:
        return apology("EMPTY FIELDS")

    password = generate_password_hash(password)
    db.execute("INSERT INTO users (id, username, hash) VALUES(?, ?, ?)", id, username, password)
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    symbols = {}
    rows = db.execute("SELECT * FROM stocks WHERE user_id = ?;", session["user_id"])
    for row in rows:
        symbols[row["symbol"]] = row["shares"]

    if request.method == "GET":
        return render_template("sell.html", symbols=symbols)

    symbol, shares = request.form.get("symbol"), int(request.form.get("shares"))

    if symbol not in symbols:
        return apology("INVALID STOCK")

    if shares > symbols[symbol]:
        return apology("NOT OWNED")

    if shares == symbols[symbol]:
        db.execute("DELETE FROM stocks WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
    else:
        db.execute("UPDATE stocks SET shares = ? WHERE user_id = ? AND symbol = ?",
                   symbols[symbol] - shares, session["user_id"], symbol)

    price = lookup(symbol)["price"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + (price * shares), session["user_id"])

    # History
    now = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
    db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted) VALUES(?, ?, ?, ?, ?);",
               session["user_id"], symbol, -shares, price, now)

    return redirect("/")
