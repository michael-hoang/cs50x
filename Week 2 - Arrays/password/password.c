// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool lower, upper, digit, symbol = false;
    int i = 0;
    while (password[i] != '\0')
    {
        if (islower(password[i]))
        {
            lower = true;
        }
        else if (isupper(password[i]))
        {
            upper = true;
        }
        else if (isdigit(password[i]))
        {
            digit = true;
        }
        else
        {
            symbol = true;
        }

        // if all requirements are met, return true
        if (upper == true && lower == true && digit == true && symbol == true)
        {
            return true;
        }

        i++;
    }

    return false;
}
