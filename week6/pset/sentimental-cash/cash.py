# Define main function
def main():
    cents = get_cents()
    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25
    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10
    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5
    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies
    # Print total number of coins to give the customer
    print(int(coins))


def get_cents():
    while True:
        try:
            n = float(input("Change owed: "))
            if n >= 0:
                return n * 100
        except ValueError:
            print("Not a valid input")


# Calculate the max quarters
def calculate_quarters(cents):
    quarters = cents // 25
    return quarters


# Calculate the max dimes
def calculate_dimes(cents):
    dimes = cents // 10
    return dimes


# Calculate the max nickels
def calculate_nickels(cents):
    nickels = cents // 5
    return nickels


# Calculate the max pennies
def calculate_pennies(cents):
    pennies = cents  # What's left
    return pennies


# Calling main
main()
