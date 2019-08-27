// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

int words;

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// Returns Index of Character
int index_of(char x)
{
    if(isalpha(x))
    {
        return tolower(x) - 'a';
    }
    return N-1;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }


    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        node *ptr = root;
        for (int i = 0; word[i] != '\0'; i++)
        {
            int ind = index_of(word[i]);

            // Create new node at i
            if (ptr->children[i] == NULL)
            {
                node *tmp = (node *)malloc(sizeof(node));

                // Error Check
                if (tmp == NULL)
                {
                    unload();
                    return false;
                }

                // Initializing newly created node childrens
                for (int j = 0; j < N; j++)
                {
                    tmp->children[j] = NULL;
                }

                // Points to next node
                ptr->children[ind] = tmp;
            }

            ptr = ptr->children[ind];
        }
        // Checks for end of word
        ptr->is_word = true;
        words++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *ptr = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if(ptr == NULL)
        {
            return false;
        }
        ptr = ptr->children[index_of(word[i])];
    }
    return ptr->is_word;
}

// recursive implementation of unload
void clear(node* ptr)
{
    for (int i = 0; i < 27; i++)
    {
        if (ptr->children[i] != NULL)
        {
            clear(ptr->children[i]);
        }
    }

    free(ptr);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    clear(root);
    return false;
}
