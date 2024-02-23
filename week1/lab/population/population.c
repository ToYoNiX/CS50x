#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size

    int size;
    do
    {
    size = get_int("Start size: ");
    }
    while(size < 9);

    // Prompt for end size

    int end;

    do
    {
        end = get_int("End size: ");
    }
    while(end < size);

    // Calculate number of years until we reach threshold

    int years = 0;

    while(size < end)
    {
        int temp = size;
        size += size / 3;
        size -= temp / 4;
        years++;
    }

    // Print number of years

    printf("Years: %i\n", years);

    return 0;
}
