#include "pather.h"
#include <string.h>
#include <stdlib.h>


int inListSize = 10;
int outListSize = 10;
int elements = 0;
int outsize = 0;
int reachedEnd = 0;
Vector2D inlist[10], outlist[10];

//check the array in case more elements need to be added. Length = # of elements, size = size of array 
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

// Used to check if the tile is valid to make a path on 
int checkTile(Vector2D tile, Pather *path)
{
	int x = tile.x;
	int y = tile.y;
	if (x < 0 || y < 0 || x > path->map->width || y > path->map->height) //make sure its within the map
	{
		return 1;
	}
	if ((path->map->map[(y * path->map->width) + x] + '0') == 1) //check it the tile is a wall
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//find the path through depth first search and draw the path if it reaches the end
void findPath(Pather *path, Vector2D parent)
{
	Vector2D nextParent;
	Vector2D drawPath[2];
	Vector2D tile[4];
	int x, tilechecker, clearToAdd;
	if (elements == 0)
	{
		inlist[0] = parent;
		elements++;
	}
	checkArray(outsize, outlist, outListSize);
	outlist[outsize] = parent;
	outsize++;
	vector2d_copy(tile[0], parent);
	vector2d_copy(tile[1], parent);
	vector2d_copy(tile[2], parent);
	vector2d_copy(tile[3], parent);
	tile[0].y += 1;
	tile[1].x += 1;
	tile[2].y -= 1;
	tile[3].x -= 1;
	for (tilechecker = 0; tilechecker < 4; tilechecker++)
	{
		clearToAdd = 1;
		if (checkTile(tile[tilechecker], path) == 0)
		{
			for (x = 0; x < elements; x++)
			{
				if (tile[tilechecker].x == inlist[x].x && tile[tilechecker].y == inlist[x].y) //add only if its not already in the inlist
				{
					clearToAdd = 0;
				}
			}
			for (x = 0; x < outsize; x++)
			{
				if (tile[tilechecker].x == outlist[x].x && tile[tilechecker].y == outlist[x].y) //add only if its not already in the outlist
				{
					clearToAdd = 0;
				}
			}
		}
		if (clearToAdd == 1)
		{
			checkArray(elements, inlist, inListSize);
			inlist[elements] = tile[tilechecker];
			elements++;
		}
	}

	//need to remove parent from inlist and sort the list.

	nextParent = inlist[elements];
	if (nextParent.x == path->end.x && nextParent.y == path->end.y)
	{
		reachedEnd = 1;
	}
	else
	{
		findPath(path, nextParent);
	}

	if (reachedEnd == 1)
	{
		drawPath[0] = parent;
		drawPath[1] = nextParent;
		tilemap_draw_path(drawPath, 2, path->map, vector2d(86, 24));
	}
}
