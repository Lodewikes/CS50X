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
	printf("check(\n)");
	// set up cursor
	node *cursor = table[hash(word)];

	// compare
	if (strcasecmp(cursor->word, word) == 0)
	{
		return true;
	}

	// traverse list looking for word
	while (cursor->next != NULL)
	{
		cursor = cursor->next;
		if (strcasecmp(cursor->word, word) == 0)
		{
			return true;
		}
	}
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
	printf("hash()\n");
	/*
	 * Used a polynomial hash function found at:
	 * Sunlisavanur. (2012, August). Polynomial Hash Function for dictionary words [web]. retrieved from 
	 * https://sunilsavanur.wordpress.com/2012/08/14/polynomial-hash-function-for-dictionary-words/
	 * */

    // TODO
	// float index, sum = 0.0;

	// for (int i = 0; j < strlen(word); i++)
	// {
	// 	sum += (int) word[j];
	// 	index += (float)((int)word[i]) * 
	// 	index += ((int)fmod(index, sum) * len) % (int) sizeof(table);
	// }
	

	// for each letter:
	int index;
   	index = (int) tolower(word[0] - 97);	
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
	printf("load()\n");
	// open dictionary file
	FILE *file = fopen(dictionary, "r");

	// allocate memory for word
	char *word = malloc(LENGTH);

	if (word == NULL)
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
	free(word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
	printf("size()\n");
    return numWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
	printf("unload()");
    // TODO
	// create tmp, pointing to the same address as cursor
	// free tmp after cursor has moved to the next pointer
	node *tmp;
	node *cursor;


	for (int i = 0; i < N; i++)
	{
		if (table[i] == NULL)
		{
			continue;
		}

		cursor = table[i];
		tmp = cursor;

		// free each node in hashmap
		while(cursor->next != NULL)
		{
			cursor = cursor->next;
			free(tmp);
			tmp = cursor;
		}
		free(cursor);
	}

    return true;
}






