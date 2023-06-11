#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char substitute(char letter, string key);

int main(int argc, string argv[])
{
    // If program is executed w/o any or w/ > 1 CL arguments
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    int key_length = strlen(key);

    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check if key contains any non-alphabetic characters.
    for (int i = 0; i < key_length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
    }

    // Check for duplicate alphabetic characters.
    for (int i = 0; i < key_length; i++)
    {
        int occurrence = 0;
        char upper_char_i = toupper(key[i]);

        for (int j = 0; j < key_length; j++)
        {
            char upper_char_j = toupper(key[j]);
            // Change letters to uppercase to compare apples with apples
            if (upper_char_i == upper_char_j)
            {
                occurrence++;
                // If letter occurs more than once then there is a duplicate.
                if (occurrence > 1)
                {
                    printf("Key must contain each letter exactly once.\n");
                    return 1;
                }
            }
        }
    }

    string plaintext = get_string("plaintext:  ");
    int length_plaintext = strlen(plaintext);
    printf("ciphertext: ");

    // Loop through each letter in plaintext and substitute it with corresponding letter in key.
    for (int i = 0; i < length_plaintext; i++)
    {
        char letter = plaintext[i];
        // Print any non-alphabetic characters without substitution.
        if (!isalpha(letter))
        {
            printf("%c", letter);
        }
        else
        {
            char cipher_letter = substitute(letter, key);
            printf("%c", cipher_letter);
        }

    }
    printf("\n");
    return 0;
}

char substitute(char letter, string key)
{
    // Check if letter is lower or upper case
    if (isupper(letter))
    {
        int letter_ascii = letter;
        // Adjust ascii value to within alphabetical index range (0-25)
        int letter_index = letter_ascii - 65;
        return toupper(key[letter_index]);
    }
    else
    {
        int letter_ascii = letter;
        int letter_index = letter_ascii - 97;
        return tolower(key[letter_index]);
    }
}