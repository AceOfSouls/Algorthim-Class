#include "tilemap.h"

// To find a path we need the map, a starting position and the goal/ending position.
typedef struct
{
	TileMap *map;
	Vector2D start, end;
}Pather;

Pather *initPather(TileMap *map);
void makeInlistLarger(int length, int size);
void makeOutlistLarger(int length, int size);
int checkTile(Vector2D tile, Pather *path);
void findPath(Pather *path, Vector2D parent);