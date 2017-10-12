#include <string.h>
#include <stdlib.h>
#include "pather.h"


//find the path and return a list of all the vector tile positions to go to the path
void findPath(pather *path)
{
	int inListSize = 10;
	int outListSize = 10;
	int elements = 1;
	Vector2D tile[4];
	Vector2D inlist[10], outlist[10];
	inlist[0] = path->start;
	int x,tilechecker;
	for (x = 0; x < elements; x++)
	{
		outlist[x] = inlist[x];
		elements--;
		vector2d_copy(tile[0], inlist[x]);
		vector2d_copy(tile[1], inlist[x]);
		vector2d_copy(tile[2], inlist[x]);
		vector2d_copy(tile[3], inlist[x]);
		tile[0].y += 1;
		tile[1].x += 1;
		tile[2].y -= 1;
		tile[3].x -= 1;
		for (tilechecker = 0; tilechecker < 4; tilechecker++)
		{
			if (checkTile(tile[tilechecker], path) == 0)
			{
				checkArray(inListSize, inlist, elements);
				inlist[elements] = tile[tilechecker];
				elements++;
			}
		}
		if (outlist[x].x == path->start.x && outlist[x].y == path->start.y)
		{
			return;
		}
	}
}

//check the array in case more elements need to be added.
void checkArray(int length, Vector2D list[], int *size)
{
	if (length - 1 >= size)
	{
		int* list = realloc(list, length * sizeof *list);
		*size *= *size;
	}
	else
		return;
}

// Used to check if the tile is valid to make a path on ]
int checkTile(Vector2D tile, pather *path)
{
	int x = tile.x;
	int y = tile.y;
	if (x < 0 || y < 0 || x > path->map.width || y > path->map.height) //make sure its within the map
	{
		return 1;
	}
	if((path->map.map[(y * path->map.width) + x] + '0') == 1) //check it the tile is a wall
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

