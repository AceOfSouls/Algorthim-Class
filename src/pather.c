#include <string.h>
#include <stdlib.h>
#include "tilemap.h"


typedef struct
{
	TileMap map;
	Vector2D start;
	Vector2D finish;
}pather;


int currentListSize1 = 10;
int currentListSize2 = 10;
Vector2D list1[10], list2[10];

//find the path and return a list of all the vector tile positions to go to the path
Vector2D findPath(pather path)
{
	 
}

//enlarge the array in case more elements need to be added.
void enlargeArray(int length, Vector2D list[])
{
	if (length - 1 >= currentListSize1)
	{
		int* list = realloc(list, length * sizeof *list);
		currentListSize1 *= currentListSize1;
	}
	else
		return;
}

// Used to check if the tile in the map is or is not a wall
int checkTile(Vector2D *tile, TileMap *themap)
{
	
	if()
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

