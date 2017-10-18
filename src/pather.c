#include "pather.h"
#include "tilemap.h"
#include "simple_logger.h"
#include <string.h>
#include <stdlib.h>


int inListSize = 10;
int outListSize = 10;
int elements = 0;
int outsize = 0;
int reachedEnd = 0;
Vector2D inlist[10], outlist[10];

//init Pather
Pather *initPather(TileMap *map)
{
	Pather *path;
	if (!map)
	{
		slog("Map not loaded.");
		exit(1);
	}
	path = (Pather *)malloc(sizeof(Pather));
	if (!path)
	{
		slog("failed to allocate pather data");
		return NULL;
	}
	memset(path, 0, sizeof(Pather));
	path->map = map;
	path->start = map->start;
	path->end = map->end;
	return path;
}


//check the array in case more elements need to be added. Length = # of elements, size = size of array 
void makeInlistLarger(int length, int size)
{
	if (length - 1 >= size)
	{
		Vector2D *outlist = realloc(outlist, size * sizeof *outlist);
		size *= size;
		inListSize = size;
	}
	else
		return;
}

void makeOutlistLarger(int length, int size)
{
	if (length - 1 >= size)
	{
		Vector2D *inlist = realloc(inlist, length * sizeof *inlist);
		size *= size;
		outListSize = size;
	}
	else
		return;
}

// Used to check if the tile is valid to make a path on 
int checkTile(Vector2D tile, Pather *path)
{
	int x = tile.x;
	int y = tile.y;
	int width = path->map->width;
	int height = path->map->height;
	if (x < 0 || y < 0 || x > width || y > height) //make sure its within the map
	{
		return 1;
	}
	if ((path->map->map[(y * width) + x] + '0') == 1) //check it the tile is a wall
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
	int x, tilechecker, clearToAdd, f;


	if (elements == 0)
	{
		inlist[0] = parent;
		elements++;
	}
	makeOutlistLarger(outsize, outListSize);
	vector2d_copy(outlist[outsize], parent);
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
			makeInlistLarger(elements, inListSize);
			vector2d_copy(inlist[elements], tile[tilechecker]);
			elements++;
		}
	}

	//need to remove parent from inlist and sort the list.
	for (x = 0; x < elements; x++)
	{
		if (inlist[x].x == parent.x && inlist[x].y == parent.y)
		{
			elements--;
			for (f = x; x <= elements; f++)
			{
				inlist[f] = inlist[f + 1];
			}
		}
	}
	
	nextParent = inlist[elements-1];

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
		vector2d_copy(drawPath[0], parent); 
		vector2d_copy(drawPath[1], nextParent);
		tilemap_draw_path(drawPath, 2, path->map, vector2d(86, 24));
	}
}
