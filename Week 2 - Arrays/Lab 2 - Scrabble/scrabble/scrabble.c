#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    int word_score = 0;
    //
    while (word[i] != '\0')
    {
        // Check if the character is an alphabet
        if (isalpha(word[i]))
        {
            char letter_lowercase = tolower(word[i]);
            int n = 0;
            // Loop through alphabet to get index number of the letter
            while (letter_lowercase != alphabet[n])
            {
                n++;
            }

            // Increment word_score by the points that are assigned to the letter
            word_score += POINTS[n];
        }

        i++;
    }

    return word_score;
}
