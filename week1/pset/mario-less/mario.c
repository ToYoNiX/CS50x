#include <cs50.h>
#include <stdio.h>

void print_number_sign(int);

int main(void)
{
    // Prompt for Height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Print pyramids of blocks

    for (int i = 1; i <= n; i++)
    {
        int spaces = n - i;
        // Print spaces
        while (spaces--)
        {
            printf(" ");
        }
        print_number_sign(i);
        printf("\n");
    }

    return 0;
}
void print_number_sign(int h)
{
    // Print number_sign
    while (h--)
    {
        printf("#");
    }
}