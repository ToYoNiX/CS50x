// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int n_of_words = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 75;
/*
    c1 * 1 + c2 * 2 + c3 * 3

    the max number is
    (25 * 1 + 25 * 2 + 25 * 3) / 2 = 75
*/

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Pointer to move around
    node *ptr = table[hash(word)];

    while (ptr != NULL)
    {
        // if found return true
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }

        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int len = strlen(word), sum = 0;

    // (c1 * 1) + (c2 * 2) + (c3 * 3)
    for (int i = 0; i < len && i < 3; i++)
    {
        sum += ((tolower(word[i]) - 'a') * (i + 1));
    }

    // return sum % 75
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the dictionary
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(dic, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        n->next = table[hash(word)];
        table[hash(word)] = n;

        n_of_words++;
    }

    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return n_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *temp = ptr->next;
            free(ptr);
            ptr = temp;
        }
    }
    return true;
}
