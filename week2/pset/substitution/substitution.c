#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Check if a valid argument
int is_a_valid_arg(int n, string s[])
{
    if (n > 2 || n == 1)
    {
        return 1;   // 1 indicates that there is no valid key
    }

    int strsize = strlen(s [1]);

    if (strsize != 26)
    {
        return 2;   // 2 indicates that the provided key doesnot have 26 chars
    }

    for (int i = 0; i < strsize; i++)
    {
        char c = tolower(s[1][i]);
        if ((s[1][i] >= '1' && s[1][i] <= '9') || (c < 'a' || c > 'z'))
        {
            return 3;   // 3 indicates that there is an invalid char in the string
        }
        for (int j = 0; j < strsize; j++)
        {
            if (i == j)
            {
                continue;   // if it's the same index it should skip it
            }
            if (s[1][i] == s[1][j])
            {
                return 4;   // 4 indicates that there is a repeated char
            }
        }
    }

    return 0; // 0 indicates that there is nothing wrong with the argument
}

// Final output function
string encrypt(string o, string arg)
{
    // calculating the size of the string
    int strsize = strlen(o);

    // encrypting the text
    for (int i = 0; i < strsize; i++)
    {
        // checking if upper case or lower case
        if (o[i] >= 'A' && o[i] <= 'Z')
        {
            o[i] = toupper(arg [o[i] - 'A']);
        }
        else if (o[i] >= 'a' && o[i] <= 'z')
        {
            o[i] = tolower(arg [o[i] - 'a']);
        }
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
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (test == 2)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (test == 3)
    {
        printf("Key must contain alphabetic characters.\n");
        return 1;
    }
    else if (test == 4)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    // geting the input from the user
    string plaintext = get_string("plaintext: ");
    string ciphertext = encrypt(plaintext, argv[1]);

    // printing the final result
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}