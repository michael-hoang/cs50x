#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

bool only_digits(string key);
char rotate(char character, int key);

int main(int argc, string argv[])
{
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        if (only_digits(key))
        {
            long long_key = atol(key);
            string plaintext = get_string("plaintext:  ");
            printf("ciphertext: ");
            // Loop through plaintext and encrypt each letter using key
            int i = 0;
            char plain_character;
            do
            {
                plain_character = plaintext[i];
                char cipher_character = rotate(plain_character, long_key);
                printf("%c", cipher_character);
                i++;
            }
            while (plaintext[i] != '\0');
            printf("\n");
            return 0;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
}

bool only_digits(string key)
{
    // Loop through each characters of the key until NUL is reached.
    int i = 0;
    while (key[i] != '\0')
    {
        // Check if any character is not(!) a digit
        if (!isdigit(key[i]))
        {
            return false;
        }
        i++;
    }
    return true;
}

char rotate(char character, int key)
{
    int char_ascii_value = character;
    int delta_ascii;
    if (!isalpha(character)) // Print character if it's a number, symbol, or whitespace.
    {
        return character;
    }
    else
    {
        if (islower(character))
        {
            delta_ascii = 97;
        }
        else
        {
            delta_ascii = 65;
        }
        // Subtract character's ASCII value by delta_ascii to work within index range 0-25.
        int index = char_ascii_value - delta_ascii;
        long cipher_index = index + key;
        while (cipher_index > 25)
        {
            cipher_index %= 26;
        }
        // Add delta_ascii back to rotated index to get ASCII value of encrypted character.
        char encrypted_char = cipher_index + delta_ascii;
        return encrypted_char;
    }
}