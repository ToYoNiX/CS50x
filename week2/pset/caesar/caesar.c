#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Check if a valid argument
int is_a_valid_arg(int n, string s[])
{
    if (n > 2 || n == 1)
    {
        return 1;   // 1 indicates that there is no valid key
    }

    // calculating the size of the string
    int strsize = strlen(s [1]);

    for (int i = 0; i < strsize; i++)
    {
        if (s[1][i] < '1' || s[1][i] > '9')
        {
            return 1;   // 1 indicates that there is no valid key
        }
    }

    return 0; // 0 indicates that there is nothing wrong with the argument
}

// Final output function
string encrypt(string o, int arg)
{
    // calculating the size of the string
    int strsize = strlen(o);

    // encrypting the text
    for (int i = 0; i < strsize; i++)
    {
        char c = o[i];

        // Check if not a char
        if (!isalpha(c))
        {
            continue;
        }

        // See the argument is bigger than 26
        while (arg >= 26)
        {
            arg -= 26;
        }

        // Final calculations
        int ascii = c + arg;

        if (ascii > 'z')
        {
            ascii -= 26;
        }
        else if (ascii > 'Z' && c <= 'Z')
        {
            ascii -= 26;
        }

        o[i] = ascii;
    }

    // return the ciphertext
    return o;
}

int main(int argc, string argv[])
{
    // check if a valid argument
    int test = is_a_valid_arg(argc, argv);
    if (test == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // geting the input from the user
    string plaintext = get_string("plaintext: ");

    int arg = atoi(argv[1]);
    string ciphertext = encrypt(plaintext, arg);

    // printing the final result
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}