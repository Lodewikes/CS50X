// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// word count
int numWords;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
	// set up cursor
	node *cursor = table[hash(word)];

	// traverse list looking for word
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

	// for each letter:
	// int index;
   	// index = (int) tolower(word[0] - 97);	
    // return index;
	
	unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
	// open dictionary file
	FILE *file = fopen(dictionary, "r");

	// allocate memory for word
	char *word = malloc(LENGTH);

	if (file == NULL)
	{
		return false;
	}

	// read file until EOF
	while (fscanf(file, "%s", word) !=  EOF)
	{
		// allocate memory for a node
		node *n = malloc(sizeof(node));
		if (n == NULL)
		{
			return false;
		}
		// create new node for each word
		strcpy(n->word, word);

		// count words
		numWords++;

		// insert node into hashmap a that location
		n->next = table[hash(word)];

		// hash word to obtain hash value
		table[hash(word)] = n;

	}
	
	fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return numWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
	// create tmp, pointing to the same address as cursor
	// free tmp after cursor has moved to the next pointer
    node *tmp;
    node *cursor;

    // loop through each node
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }

        cursor = table[i];
        tmp = cursor;

        // free memory until end
        while (cursor->next != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        free(cursor);
    }
    return true;

}






