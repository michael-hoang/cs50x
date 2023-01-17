#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string message = get_string("Message: ");
    int i = 0;
    // Loop through each char in string until NUL is reached.
    while (message[i] != '\0')
    {
        int ascii_code = (int) message[i]; // Convert character to its ascii value
        int byte[8]; // array of size 8 (for 8 bits)
        int quotient = ascii_code;
        // Assign bit to 0 or 1 starting with the last index of 7 in the array
        int bit_index = 7;
        do
        {
            int remainder = quotient % 2;
            if (remainder == 0)
            {
                byte[bit_index] = 0;
            }
            else
            {
                byte[bit_index] = 1;
            }
            quotient = (quotient - remainder) / 2;
            bit_index--;
        }
        while (bit_index >= 0);
        // Print bulb starting with the first index of 0 in the array
        for (bit_index = 0; bit_index < 8; bit_index++)
        {
            print_bulb(byte[bit_index]);
        }
        printf("\n");
        i++;
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
