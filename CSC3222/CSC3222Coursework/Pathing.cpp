#include "Pathing.h"
#include <limits>
#include <algorithm>

int Pathing::getTileIndex(int x, int y) {
	return x + (y * MAP_WIDTH);
}

void Pathing::addIfPossible(std::vector<MapNode*>* openList, MapNode* node, int destX, int destY) {
	node->updateHeuristic(destX, destY);
	if (!node->isClosed && node->isTraversable) {
		openList->push_back(node);
	}
}

void Pathing::addToClosedList(std::vector<MapNode*>* closedList, MapNode* node) {
	node->isClosed = true;
	closedList->push_back(node);
}

void Pathing::removeFromOpenList(std::vector<MapNode*>* openList, MapNode* node) {
	auto it = std::find(openList->begin(), openList->end(), node);
	if (it != openList->end()) {
		openList->erase(it);
	}
}

void Pathing::addAvaliableNodes(std::vector<MapNode*>* openList, int tileX, int tileY, int destX, int destY) {
	addIfPossible(openList, &gameMap[getTileIndex(tileX + 1, tileY)], destX, destY);
	addIfPossible(openList, &gameMap[getTileIndex(tileX - 1, tileY)], destX, destY);
	addIfPossible(openList, &gameMap[getTileIndex(tileX, tileY + 1)], destX, destY);
	addIfPossible(openList, &gameMap[getTileIndex(tileX, tileY - 1)], destX, destY);
}

std::vector<MapNode*> Pathing::getNeighbouringNodes(int tileX, int tileY, int destX, int destY) {
	std::vector<MapNode*> neighbourNodes;
	neighbourNodes.reserve(3);
	if (tileX < MAP_WIDTH - 2) {
		MapNode* neighbour = &gameMap[getTileIndex(tileX + 1, tileY)];
		if (!neighbour->isClosed && neighbour->isTraversable) {
			neighbour->updateHeuristic(destX, destY);
			
			if (neighbour->bestParent != nullptr) {
				neighbour->g = neighbour->bestParent->g + neighbour->cost;
			}
			neighbour->g = neighbour->cost;

			neighbourNodes.push_back(neighbour);
		}
	}
	if (tileX > 0) {
		MapNode* neighbour = &gameMap[getTileIndex(tileX - 1, tileY)];
		if (!neighbour->isClosed && neighbour->isTraversable) {
			neighbour->updateHeuristic(destX, destY);

			if (neighbour->bestParent != nullptr) {
				neighbour->g = neighbour->bestParent->g + neighbour->cost;
			}
			neighbour->g = neighbour->cost;

			neighbourNodes.push_back(neighbour);
		}
	}
	if (tileX < MAP_WIDTH - 2) {
		MapNode* neighbour = &gameMap[getTileIndex(tileX, tileY + 1)];
		if (!neighbour->isClosed && neighbour->isTraversable) {
			neighbour->updateHeuristic(destX, destY);

			if (neighbour->bestParent != nullptr) {
				neighbour->g = neighbour->bestParent->g + neighbour->cost;
			}
			neighbour->g = neighbour->cost;

			neighbourNodes.push_back(neighbour);
		}
	}
	if (tileX > 0) {
		MapNode* neighbour = &gameMap[getTileIndex(tileX, tileY - 1)];
		if (!neighbour->isClosed && neighbour->isTraversable) {
			neighbour->updateHeuristic(destX, destY);

			if (neighbour->bestParent != nullptr) {
				neighbour->g = neighbour->bestParent->g + neighbour->cost;
			}
			neighbour->g = neighbour->cost;

			neighbourNodes.push_back(neighbour);
		}
	}

	return neighbourNodes;
}

MapNode* Pathing::getTargetTile(MapNode* endNode) {
	MapNode* previousNode = nullptr;
	for (MapNode* node = endNode; node->bestParent != nullptr; node = node->bestParent) {
		//std::cout << node->x << "," << node->y << " >>  " << std::endl;
		previousNode = node;
	}

	return previousNode;
}


MapNode* Pathing::getBestNode(std::vector<MapNode*>* openList) {
	float bestFValue = std::numeric_limits<float>::infinity();
	MapNode* bestNode = nullptr;

	for (MapNode* node : *openList) {
		float newF = node->f();

		if (newF <= bestFValue) {
			bestFValue = newF;
			bestNode = node;
		}
	}

	return bestNode;
}

void Pathing::resetMap() {
	const int NODE_COUNT = MAP_WIDTH * MAP_HEIGHT;

	if (gameMap == nullptr) {
		gameMap = new MapNode[NODE_COUNT];
	}

	for (int i = 0; i < NODE_COUNT; ++i) {
		gameMap[i] = templateMap[i];
	}
}

void Pathing::resetMapInstance() {
	const int NODE_COUNT = MAP_WIDTH * MAP_HEIGHT;

	gameMap = new MapNode[NODE_COUNT];

	for (int i = 0; i < NODE_COUNT; ++i) {
		gameMap[i] = templateMap[i];
	}
}

NCL::Maths::Vector2 Pathing::getDirection(float sourceXPos, float sourceYPos, float destXPos, float destYPos) {
	int startX = round(sourceXPos / TILE_WIDTH);
	int startY = round(sourceYPos / TILE_WIDTH);
	int endX = round(destXPos / TILE_WIDTH);
	int endY = round(destYPos / TILE_WIDTH);

	std::vector<MapNode*> openList;
	std::vector<MapNode*> closedList;
	openList.reserve(MAP_WIDTH * MAP_HEIGHT);
	closedList.reserve(MAP_WIDTH * MAP_HEIGHT);

	MapNode* startNode = &gameMap[getTileIndex(startX, startY)];
	MapNode* endNode = &gameMap[getTileIndex(endX, endY)];
	startNode->updateHeuristic(endX, endY);
	endNode->updateHeuristic(endX, endY);

	//std::cout << "Node: " << startNode->x << "," << startNode->y << "[g=" << startNode->g << "][h=" << startNode->h << "]" << std::endl;

	openList.push_back(startNode);

	while (!openList.empty()) {
		MapNode* bestNode = getBestNode(&openList);
		//std::cout << "Best Node: " << bestNode->x << "," << bestNode->y << "[g=" << bestNode->g << "][h=" << bestNode->h << "]" << std::endl;

		if (bestNode == endNode) {
			//std::cout << "Best route found!" << std::endl;
			break;
		}

		for (MapNode* node : getNeighbouringNodes(bestNode->x, bestNode->y, endX, endY)) {
			//std::cout << "Node: " << node->x << "," << node->y << "[g=" << node->g << "][h=" << node->h << "]" << std::endl;

			// If not in openlist
			if (std::find(openList.begin(), openList.end(), node) == openList.end()) {
				node->bestParent = bestNode;
				node->g = bestNode->g + (std::max)(node->cost, bestNode->cost);
				openList.push_back(node);
				continue;
			}

			//std::cout << "   if " << node->f() << ">=" << bestNode->f() << "?" << std::endl;
			if (node->f() >= bestNode->f()) {
				continue;
			}

			node->bestParent = bestNode;
			node->g = bestNode->g + node->cost;
		}

		removeFromOpenList(&openList, bestNode);
		addToClosedList(&closedList, bestNode);
	}

	MapNode* nextTile = getTargetTile(endNode);
	if (nextTile == nullptr) {
		return NCL::Maths::Vector2(2, 2);
	}

	return NCL::Maths::Vector2(nextTile->x * TILE_WIDTH, nextTile->y * TILE_WIDTH);
}

void Pathing::setGameMap(MapNode* gameMap, int mapWidth, int mapHeight, int tileWidth) {
	this->templateMap = gameMap;
	MAP_WIDTH = mapWidth;
	MAP_HEIGHT = mapHeight;
	TILE_WIDTH = tileWidth;

	resetMap();
}