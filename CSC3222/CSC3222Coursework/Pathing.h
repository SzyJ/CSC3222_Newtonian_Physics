#include "MapNode.h"
#include "../../Common/Vector2.h"

/**
 * Implementation of A* algorithm
 */

using namespace NCL;

class Pathing {
	MapNode* gameMap;
	int MAP_WIDTH;
	int MAP_HEIGHT;

	Pathing(MapNode* gameMap, int mapWidth, int mapHeight)
		: gameMap(gameMap), MAP_WIDTH(mapWidth), MAP_HEIGHT(mapHeight)
	{}

	~Pathing()
	{
		delete[] gameMap;
	}

	NCL::Maths::Vector2 getDirection(float sourceXPos, float sourceYPos, float destXPos, float destYPos);

	void setGameMap(MapNode* gameMap, int mapWidth, int mapHeight);
};