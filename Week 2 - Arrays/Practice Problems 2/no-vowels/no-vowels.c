// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string word);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string converted_word = replace(argv[1]);
        printf("%s\n", converted_word);
    }
    else
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
}

string replace(string word)
{
    // Iterate through each char in string until NUL
    int i = 0;
    while (word[i] != '\0')
    {
        switch (word[i]) // Switch alpha char with numeric char
        {
            case 'a':
                word[i] = '6';
                break;

            case 'e':
                word[i] = '3';
                break;

            case 'i':
                word[i] = '1';
                break;

            case 'o':
                word[i] = '0';
                break;
        }

        i++;
    }

    return word;
}