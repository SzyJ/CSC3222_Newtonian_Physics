#pragma once

#include "MapNode.h"
#include "../../Common/Vector2.h"
#include <vector>

/**
 * Implementation of A* algorithm
 */

class Pathing {

private:
	const MapNode* templateMap;
	MapNode* gameMap;
	int MAP_WIDTH;
	int MAP_HEIGHT;
	int TILE_WIDTH;

	int getTileIndex(int x, int y);

	void addAvaliableNodes(std::vector<MapNode*>* openList, int tileX, int tileY, int destX, int destY);
	std::vector<MapNode*> getNeighbouringNodes(int tileX, int tileY, int destX, int destY);

	static void addToClosedList(std::vector<MapNode*>* closedList, MapNode* node);
	static void removeFromOpenList(std::vector<MapNode*>* openList, MapNode* node);
	static void addIfPossible(std::vector<MapNode*>* openList, MapNode* node, int destX, int destY);
	static MapNode* getBestNode(std::vector<MapNode*>* openList);
	static MapNode* getTargetTile(MapNode* endNode);

	void resetMap();

public:
	Pathing(MapNode* gameMap, int mapWidth, int mapHeight, int tileWidth)
		: templateMap(gameMap), MAP_WIDTH(mapWidth), MAP_HEIGHT(mapHeight), TILE_WIDTH(tileWidth)
	{
		const int NODE_COUNT = mapWidth * mapHeight;
		gameMap = new MapNode[NODE_COUNT];

		resetMap();
	}

	Pathing()
		: templateMap(nullptr), MAP_WIDTH(0), MAP_HEIGHT(0), TILE_WIDTH(0)
	{}

	~Pathing()
	{}

	NCL::Maths::Vector2 getDirection(float sourceXPos, float sourceYPos, float destXPos, float destYPos);

	void setGameMap(MapNode* gameMap, int mapWidth, int mapHeight, int tileWidth);
	void resetMapInstance();
};
