#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Creating a struct just for return in calculation function
struct strcalc
{
    float S;  // sentences
    float L;  // letters
    float W;  // words
};

// A function prototype
struct strcalc calcreq(string text);

int main(void)
{
    // Get input text
    string text = get_string("Text: ");

    // Calling the function that do the math
    struct strcalc calculatons = calcreq(text);

    // Doing some math
    float L = (calculatons.L / calculatons.W) * 100,
          S = (calculatons.S / calculatons.W) * 100,
          index = 0.0588 * L - 0.296 * S - 15.8;

    // The output
    index = round(index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)index);
    }

    return 0;
}

// Calculatons
struct strcalc calcreq(string text)
{
    int strsize = strlen(text);

    // Final calculations
    struct strcalc final;
    final.L = 0;
    final.S = 0;
    final.W = 0;

    for (int i = 0; i < strsize; i++)
    {
        char c = toupper(text [i]);

        // Check end of the sentences
        if (c == '.' || c == '!' || c == '?')
        {
            final.S++;
            continue;
        }

        // Check if is an alphabet
        if (c >= 'A' && c <= 'Z')
        {
            final.L++;
        }
        // Check for words
        else if (c == ' ')
        {
            final.W++;
        }
    }
    // Adding one char because there is no space at the end of the string
    final.W++;
    return final;
}