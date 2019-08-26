// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        int hash_index;

        // Get bucket number in which the word belongs
        hash_index = hash(word);

        // Allocating memory to store the new word
        node *new = (node *)malloc(sizeof(node));

        // Error Check :)
        if (new == NULL)
        {
            unload();
            return false;
        }

        // Assigning Data to new node
        strcpy(new->word, word);

        // Adding new to the start of the hash table
        new->next = hashtable[hash_index];
        hashtable[hash_index] = new;

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        node *ptr = hashtable[i];
        while (ptr != NULL)
        {
            count++;
            ptr = ptr->next;
        }
    }
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_index;
    node *ptr;

    // Getting bucket number in which word can be expected to be.
    hash_index = hash(word);

    // Travesing that bucket in search of the word
    ptr = hashtable[hash_index];
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return 1;
        }
        ptr = ptr->next;
    }

    // return 0 if the word is not found in the dicionary
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr;

        while (hashtable[i] != NULL)
        {
            ptr = hashtable[i];
            hashtable[i] = hashtable[i]->next;
            free(hashtable[i]);
        }
        free(hashtable[i]);
    }
    return true;
}
