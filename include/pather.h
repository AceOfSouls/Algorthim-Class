#include "tilemap.h"

// To find a path we need the map, a starting position and the goal/ending position.
typedef struct
{
	TileMap *map;
	Vector2D start, end;
	int inListSize;
	int outListSize;
	int elements;
	int outsize;
	int reachedEnd;
	Vector2D inlist[10], outlist[10];
}Pather;

Pather *initPather(TileMap *map);
void makeInlistLarger(int length, int size, Pather *path);
void makeOutlistLarger(int length, int size, Pather *path);
int checkTile(Vector2D tile, Pather *path);
void findPath(Pather *path, Vector2D parent);