# Prompt the user for height
def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0 and n < 9:
                return n
        except ValueError:
            print("Not a integer")


# Print the double half-pyramid
height = get_height()
for i in range(height):
    blocks = i + 1
    spaces = height - 1 - i
    print(spaces * " " + blocks * "#" + "  " + blocks * "#")
