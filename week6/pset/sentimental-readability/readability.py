# Defining main function
def main():
    text = input("Text: ")
    L = (letter_count(text.lower()) / word_count(text)) * 100
    S = (sentence_count(text) / word_count(text)) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    # Final Output
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


# Counting words
def word_count(s):
    # Adding one char because there is no space at the end of the string
    return s.count(" ") + 1


# Counting sentences
def sentence_count(s):
    # Count each end of a sentence
    return s.count("!") + s.count(".") + s.count("?")


# Counting letters
def letter_count(s):
    counter = 0
    for c in s:
        # Check if is an alphabet
        if c >= "a" and c <= "z":
            counter += 1
    return counter


# Calling main
main()
