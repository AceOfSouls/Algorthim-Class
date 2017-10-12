#include "tilemap.h"

// To find a path we need the map, a starting position and the goal/ending position.
typedef struct
{
	TileMap map;
	Vector2D start;
	Vector2D end;
}pather;
