#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int last_index = strlen(input) - 1;
    int int_digit = (int) input[last_index] - 48; // Subtract 48 from ASCII value digit to get to integer digit.
    // Shorten string by replacing last index with '\0'
    input[last_index] = '\0';
    if (input[0] != '\0')
    {
        printf("%i", convert(input));
    }
    return int_digit;
}