#include <cs50.h>
#include <stdio.h>
#include <string.h>

void print_bulb(int bit);
void print_str(string s);

int main(void)
{
    // Prompt the user for the message
    string message = get_string("Message: ");

    // Printing the bulbs
    print_str(message);
    return 0;
}

void print_str(string s)
{
    // Geting the size of the input
    int strsize = strlen(s);
    for (int i = 0; i < strsize; i++)
    {
        char c = s[i];

        // Getting every char of the pinary code
        for (int j = 7; j >= 0; --j)
        {
            // Printing every bulb
            print_bulb(((c & (1 << j)) ? '1' : '0') - '0');
        }
        putchar('\n');
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}