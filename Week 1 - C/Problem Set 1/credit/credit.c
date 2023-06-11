#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for credit card number
    long cc_num;
    do
    {
        cc_num = get_long("Number: ");
    }
    while (cc_num < 1);

    long cc_num_copy = cc_num;

    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    // Add the sum to the sum of the digits that weren’t multiplied by 2.
    int last_digit;
    int i = 1;
    int sum_of_all_digits = 0;
    do
    {
        // printf("i: %i, ", i);
        last_digit = cc_num % 10;
        // printf("last_digit: %i\n", last_digit);
        cc_num = (cc_num - last_digit) / 10;
        if (i % 2 == 0)
        {
            int last_digit_x2 = last_digit * 2;
            // printf("last_digit_x2: %i\n", last_digit_x2);
            last_digit = last_digit_x2;
            if (last_digit_x2 > 9)
            {
                int primary_last_digit = last_digit_x2 % 10;
                int secondary_last_digit = (last_digit_x2 - primary_last_digit) / 10;
                last_digit = primary_last_digit + secondary_last_digit;
            }
        }

        // printf("last_digit: %i\n", last_digit);
        sum_of_all_digits += last_digit;
        last_digit = 0;
        i++;
    }
    while (cc_num > 0);
    // printf("%i\n", sum_of_all_digits);

    // If total's last digit is 0, number is valid.
    int is_last_digit_0 = sum_of_all_digits % 10;

    // Get first two digits of cc_num
    long cc_num_remain = cc_num_copy;
    do
    {
        last_digit = cc_num_remain % 10;
        cc_num_remain = (cc_num_remain - last_digit) / 10;
    }
    while (cc_num_remain > 100);

    // printf("%ld", cc_num_remain);

    // Get length of credit card
    int cc_length = i - 1;

    // printf("%i\n", cc_length);

    // Credit card network validation.
    string card_network;

    if (is_last_digit_0 == 0)
    {
        if ((cc_num_remain == 34 || cc_num_remain == 37) && (cc_length == 15))
        {
            card_network = "AMEX";
        }
        else if ((cc_num_remain >= 40 && cc_num_remain < 50) && (cc_length == 13 || cc_length == 16))
        {
            card_network = "VISA";
        }
        else if ((cc_num_remain > 50 && cc_num_remain < 56) && (cc_length == 16))
        {
            card_network = "MASTERCARD";
        }
        else
        {
            card_network = "INVALID";
        }
    }
    else
    {
        card_network = "INVALID";
    }

    printf("%s\n", card_network);
}
