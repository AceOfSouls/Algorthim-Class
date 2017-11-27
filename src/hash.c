#include <stdlib.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "simple_logger.h"
#include "hash.h"

hashmap_t *hm_create(int size)
{
	hashmap_t *hashmap = NULL;
	int i;

	if (size < 1)
	{
		slog("invalid hashmap size");
		return NULL;
	}

	if ((hashmap = malloc(sizeof(hashmap_t))) == NULL)
	{
		slog("unable to allocate memory for hashmap");
		return NULL;
	}

	if ((hashmap->map = malloc(sizeof(entry_t *)* size)) == NULL)
	{
		slog("unable to allocate pointer for hashmap head");
		return NULL;
	}

	for (i = 0; i < size; i++)
	{
		hashmap->map[i] = NULL;
	}

	hashmap->size = size;
	hashmap->count = 0;

	return hashmap;
}

// make a new key and shape entry to be added
entry_t *newentry(char *key, char *data)
{
	entry_t *new;

	if ((new = malloc(sizeof(entry_t))) == NULL) {
		return NULL;
	}

	if ((new->key = strdup(key)) == NULL) {
		return NULL;
	}

	if ((new->data = strdup(data)) == NULL) {
		return NULL;
	}

	new->next = NULL;

	return new;
}

//create the hash for the map
int hash(hashmap_t *hashmap, char *key)
{
	int i;
	int hashed = 0;

	if (hashmap == NULL)// Check to make sure it has a hash map
	{
		slog("no hashmap found while hashing");
		return -1;
	}

	for (i = 0; key[i] != '\0'; i++)
	{
		hashed += key[i];
	}
	return (hashed % hashmap->size);
}

// delete the entire map
void deletemap(hashmap_t *hashmap)
{
	int i = 0;

	if (hashmap == NULL)// Check to make sure it has a hash map
	{
		slog("no hashmap found while deleting");
		return;
	}

	for (i = 0; i < hashmap->size; i++)
	{
		if (hashmap->map[i] != NULL)
		{
			//free each entry
			free(hashmap->map[i]);
		}
	}
	//free map
	free(hashmap);
}

//insert data into the hashmap
void hm_insert(hashmap_t *hashmap, char *key, char *data)
{
	int hashvalue = hash(hashmap, key);
	entry_t *newE = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	// Check hash value to make sure it is positive
	if (hashvalue < 0)
	{
		slog("a negative key value has been entered");
	}

	next = hashmap->map[hashvalue];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0)
	{
		last = next;
		next = next->next;
	}

	//Check if key is already in it
	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0)
	{
		free(next->data);
		next->data = data;
	}
	else //insert new key-data entry
	{
		newE = newentry(key, data);
		hashmap->count += 1;

		if (next == hashmap->map[hashvalue]) //In the begining
		{
			newE->next = next;
			hashmap->map[hashvalue] = newE;
		}
		else if (next == NULL) // At the end
		{
			last->next = newE;
		}
		else //Middle 
		{
			newE->next = next;
			last->next = newE;
		}
	}

}

//expand the hash map once all spaces are filled
void expandhashmap(hashmap_t *hm, int newsize)
{
	int i = 0;
	hashmap_t *newmap, *oldmap;
	entry_t *curentry;

	if (hm == NULL)// Check to make sure it has a hash map
	{
		slog("no hashmap found while expanding");
		return;
	}

	newmap = hm_create(newsize);
	oldmap = hm;

	while (i < hm->size)
	{
		curentry = hm->map[i];
		while (curentry != 0)
		{
			hm_insert(newmap, curentry->key, curentry->data);
			curentry = curentry->next;
		}
		i++;
	}
	deletemap(oldmap);
	hm->map = newmap->map;
	hm->size = newmap->size;
}

//set the data
void hm_set(hashmap_t *hashmap, char *key, char *data)
{
	if (hashmap == NULL)
	{
		slog("no hashmap found while setting");
		return;
	}

	if (hashmap->count >= hashmap->size)
	{
		expandhashmap(hashmap, hashmap->size * 2);
		hm_insert(hashmap, key, data);
	}
	else
	{
		hm_insert(hashmap, key, data);
	}
}

//get the shape from the hash map using the key
char *hm_get(hashmap_t *hashmap, char *key)
{
	int hashvalue = hash(hashmap, key);
	entry_t *entry;

	entry = hashmap->map[hashvalue];
	while (entry != NULL && entry->key != NULL && strcmp(key, entry->key) > 0)
	{
		entry = entry->next;
	}

	if (entry == NULL || entry->key == NULL || strcmp(key, entry->key) != 0)
	{
		slog("entry not found");
		return NULL;
	}
	else
	{
		return entry->data;
	}
}

/*
int main(int argc, char **argv) {

	hashmap_t *hashmap = hm_create(65536);

	hm_set(hashmap, "key1", "inky");
	hm_set(hashmap, "key2", "pinky");
	hm_set(hashmap, "key3", "blinky");
	hm_set(hashmap, "key4", "floyd");
	hm_set(hashmap, "key5", "flower");


	printf("%s\n", hm_get(hashmap, "key1"));
	printf("%s\n", hm_get(hashmap, "key2"));
	printf("%s\n", hm_get(hashmap, "key3"));
	printf("%s\n", hm_get(hashmap, "key4"));

	deletemap(hashmap);

	return 0;
}*/