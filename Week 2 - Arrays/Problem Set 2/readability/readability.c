#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int count_letters(string text);
int count_sentences(string text);
int count_words(string text);

int main(void)
{
    // Prompt user for text.
    string text = get_string("Text: ");
    int letter_count = count_letters(text);
    // printf("letter count: %i\n", letter_count);
    int word_count = count_words(text);
    // printf("word count: %i\n", word_count);
    int sentence_count = count_sentences(text);
    // printf("sentence count: %i\n", sentence_count);
    double L = (double) letter_count / (double) word_count * 100; // Type casting: converting one data type to another
    // printf("L: %f\n", L);
    double S = (double) sentence_count / (double) word_count * 100; // Type casting: converting one data type to another
    // printf("S: %f\n", S);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int letter_count = 0;
    int i = 0;
    // Loop through each character in string until NUL is reached.
    while (text[i] != '\0')
    {
        // Increment letter_count if character is an alphabet.
        if (isalpha(text[i]))
        {
            letter_count++;
        }
        i++;
    }
    return letter_count;
}

int count_words(string text)
{
    int word_count = 0;
    int i = 0;
    // Loop through each character in string until NUL is reached.
    while (text[i] != '\0')
    {
        // Increment word_count for every whitespace characters.
        if (text[i] == ' ')
        {
            word_count++;
        }
        i++;
    }
    // If first character is not NUL, increment word_count to account for last word.
    if (i > 0)
    {
        word_count++;
        return word_count;
    }
    // No words were entered.
    else
    {
        return 0;
    }
}

int count_sentences(string text)
{
    int sentence_count = 0;
    int i = 0;
    // Loop through each character in string until NUL is reached.
    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence_count++;
        }
        i++;
    }
    return sentence_count;
}