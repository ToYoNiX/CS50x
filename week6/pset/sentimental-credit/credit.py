# Define main function
def main():
    # Promt the user for input
    card = get_card()
    # Counting Digits
    digits = digits_count(card)
    valid = isvalid(card)
    # This is for checking
    card //= pow(10, (digits - 2))
    if (digits == 13 or digits == 16) and card // 10 == 4 and valid:
        print("VISA")
    # AMEX Check
    elif digits == 15 and (card == 34 or card == 37) and valid:
        print("AMEX")
    # MASTER CARD Check
    elif (
        valid
        and digits == 16
        and (card == 51 or card == 52 or card == 53 or card == 54 or card == 55)
    ):
        print("MASTERCARD")
    else:
        print("INVALID")


def get_card():
    while True:
        try:
            n = int(input("Number: "))
            if n > 0:
                return n
        except ValueError:
            print("Not a number")


# Calculate number digits
def digits_count(n):
    digits = 0
    while n != 0:
        digits += 1
        n //= 10
    return digits


# Calculate The sum of multiplied digits
def sum_digits_multiplied(n):
    n //= 10
    sum = 0
    while n != 0:
        temp = (n % 10) * 2
        if temp < 10:
            sum += temp
        else:
            sum += temp % 10
            temp //= 10
            sum += temp
        n //= 100
    return sum


# Calculate The sum of not multiplied digits
def sum_digits_not_multiplied(n):
    sum = 0
    while n != 0:
        sum += n % 10
        n //= 100
    return sum


# Check if the number is valid or not
def isvalid(n):
    sum_M = sum_digits_multiplied(n)
    sum_NotM = sum_digits_not_multiplied(n)
    temp = sum_M + sum_NotM
    if temp % 10 == 0:
        return True
    else:
        return False


# Calling main
main()
