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

    // 1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.

    int last_digit;
    int i = 1; // indicator to multiply every other digit by 2 if 'i' is even
    long remaining_cc_num = cc_num;
    int sum_of_all_product_digits = 0;
    int sum_of_all_non_product_digits = 0;
    do
    {
        last_digit = remaining_cc_num % 10;
        if (i % 2 == 0)
        {
            int last_digit_x2 = last_digit * 2;
            int product_last_digit;
            int sum_of_product_digits = 0;

            do
            {
                product_last_digit = last_digit_x2 % 10;
                sum_of_product_digits += product_last_digit;
                int product_minus_lastDigit = last_digit_x2 - product_last_digit;
                last_digit_x2 = product_minus_lastDigit / 10;
            }
            while (product_last_digit != last_digit_x2);

            sum_of_all_product_digits += sum_of_product_digits;
        }
        else
        {
            sum_of_all_non_product_digits += last_digit;
        }

        long cc_minus_lastDigit = remaining_cc_num - last_digit;
        remaining_cc_num = cc_minus_lastDigit / 10;
        i++;
    }
    while (last_digit != remaining_cc_num);

    // printf("%i\n", sum_of_all_product_digits);

    // 2. Add the sum to the sum of the digits that weren’t multiplied by 2.

    int sum_total = sum_of_all_product_digits + sum_of_all_non_product_digits;

    // printf("%i\n", sum_total);

    // 3. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

    // Get first 2 digits of credit card number.
    do
    {
        long remainder = cc_num % 10;
        long cc_num_minus_remainder = cc_num - remainder;
        cc_num = cc_num_minus_remainder / 10;
    }
    while (cc_num > 100);

    // Credit card network validation.
    string card_network;
    if (cc_num == 34 || cc_num == 37)
    {
        card_network = "AMEX";
    }
    else if (cc_num >= 40 && cc_num < 50)
    {
        card_network = "VISA";
    }
    else if (cc_num > 50 && cc_num < 56)
    {
        card_network = "MASTERCARD";
    }
    else
    {
        card_network = "INVALID";
    }

    if (sum_total % 10 == 0)
    {
        printf("%s\n", card_network);
    }
    else
    {
        printf("INVALID\n");
    }
}