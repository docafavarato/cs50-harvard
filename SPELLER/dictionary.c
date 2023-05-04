#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Hash table
node *table[26];


unsigned int hash(const char *word)
{

    return toupper(word[0]) - 'A';
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    unsigned int bucket = hash(word);

    for (node *ptr = table[bucket]; ptr != NULL; ptr = ptr->next)
    {

        if (strcasecmp(ptr->word, word) == 0)
        {

            return true;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }


    for (int i = 0; i < 26; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];


    while (fscanf(file, "%s", word) != EOF)
    {

        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }
        strcpy(new_node->word, word);
        new_node->next = NULL;


        unsigned int bucket = hash(word);

        new_node->next = table[bucket];
        table[bucket] = new_node;
    }

    // Close the dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    unsigned int count = 0;

    for (int i = 0; i < 26; i++)
    {
        // Traverse the linked list in the bucket
        for (node *ptr = table[i]; ptr != NULL; ptr = ptr->next)
        {

            count++;
        }
    }

    // Return the total number of words
    return count;
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through each bucket in the hash table
    for (int i = 0; i < 26; i++)
    {
        // Create a pointer to the current node and the next node
        node *current = table[i];
        node *next = NULL;

        // Traverse the linked list and free each node
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
    }

    return true;
}
