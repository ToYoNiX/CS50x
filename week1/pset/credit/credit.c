#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// For Check if the number is valid
int digits_not_multiplied(long);
int digits_multiplied(long);
int digits_counter(long);

bool isvalid(long);

int main(void)
{
    // Prompt for Credit Number
    long input = get_long("Number: ");

    // Counting Digits
    int digits = digits_counter(input),
        valid  = isvalid(input);

    // This is for checking
    input /= pow(10, (digits - 2));

    // VISA Check
    if ((digits == 13 || digits == 16) && input / 10 == 4 && valid)
    {
        printf("VISA\n");
    }
    // AMEX Check
    else if (digits == 15 && (input == 34 || input == 37) && valid)
    {
        printf("AMEX\n");
    }
    // MASTER CARD Check
    else if (valid && digits == 16 && (input == 51 || input == 52 || input == 53 || input == 54 || input == 55))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }


    return 0;
}

int digits_not_multiplied(long i)
{
    // Calculate The sum of not multiplied digits
    int sum = 0;

    while (i != 0)
    {
        sum += i % 10;
        i /= 100;
    }
    return sum;
}

int digits_multiplied(long i)
{
    // Calculate The sum of multiplied digits
    i /= 10;
    int sum = 0;

    while (i != 0)
    {
        int temp = (i % 10) * 2;
        if (temp < 10)
        {
            sum += temp;
        }
        else
        {
            sum += (temp % 10);
            temp /= 10;
            sum += temp;
        }
        i /= 100;
    }
    return sum;
}

int digits_counter(long i)
{
    // Calculate digits of number
    int digits = 0;

    while (i != 0)
    {
        digits++;
        i /= 10;
    }
    return digits;
}

bool isvalid(long i)
{
    // Check if the number is valid or not
    int sum_M = digits_multiplied(i),
        sum_NotM = digits_not_multiplied(i),
        temp;
    temp = sum_M + sum_NotM;
    if (temp % 10 == 0)
    {
        return 1;
    }
    return 0;
}