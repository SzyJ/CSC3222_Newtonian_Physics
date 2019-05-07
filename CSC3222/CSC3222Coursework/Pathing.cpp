#include "Pathing.h"

NCL::Maths::Vector2 Pathing::getDirection(float sourceXPos, float sourceYPos, float destXPos, float destYPos) {
	// TODO... Pathing logic

	return NCL::Maths::Vector2(0, 0);
}

void Pathing::setGameMap(MapNode* gameMap, int mapWidth, int mapHeight) {
	this->gameMap = gameMap;
	MAP_WIDTH = mapWidth;
	MAP_HEIGHT = mapHeight;
}