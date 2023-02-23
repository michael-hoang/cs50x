// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table 12161
const unsigned int N = 12161;

// Hash table
node *table[N];

// Keep track of total words
int total_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_code = hash(word);
    node *cursor = table[hash_code];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int ascii_sum = 0;
    int word_length = strlen(word);
    int first_letter = tolower(word[0]);
    int second_letter = tolower(word[1]);
    int third_letter = tolower(word[2]);
    int last_letter = tolower(word[word_length - 1]);
    for (int i = 0; i < word_length; i++)
    {
        ascii_sum += tolower(word[i]);
    }

    int product;
    if (word_length % 2 == 0)
    {
        product = ascii_sum * (first_letter + second_letter);
        if (word_length < 7)
        {
            product *= word_length;
        }
        else
        {
            product *= word_length * 13;
        }
    }
    else if (word_length > 2)
    {
        product = ascii_sum * (first_letter + third_letter);
        if (word_length < 6)
        {
            product *= word_length * 7;
        }
        else
        {
            product *= word_length * 11;
        }
    }
    else
    {
        product = ascii_sum * first_letter;
    }

    if (product % 13 < 7)
    {
        product = (product + word_length) * (ascii_sum - word_length);
    }
    else
    {
        product = (product - ascii_sum) * word_length;
    }

    product *= last_letter;
    return product % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH  + 1];
    unsigned int hash_code;
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(new_node->word, word);
        hash_code = hash(word);
        new_node->next = table[hash_code];
        table[hash_code] = new_node;
        total_words++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}