#include "GameMap.h"
#include "GameSimsRenderer.h"
#include "TextureManager.h"
#include "../../Common/Assets.h"
#include "../../Common/TextureLoader.h"
#include "CollisionVolume.h"
#include "WallTile.h"
#include "MapNode.h"
#include <fstream>
#include <iostream>

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

//These are all in format: x pos, y pos, xsize, ysize
Vector4 GameMap::tileSpecs[MAX_TILES] = {
	Vector4(101,13,16,16),	//Flat
	Vector4(96,56,16,16),	//Wall
	Vector4(144,56,16,16),	//Rough
};

//Random rough looking tiles for variety
Vector4 randomRoughTiles[4] = {
	Vector4(144,40,16,16),	//
	Vector4(144,56,16,16),	//
	Vector4(160,40,16,16),	//
	Vector4(160,56,16,16),	//
};

Vector4 buildingTypes[4] = {
	Vector4(376,56,32,48),	//Red teleporter
	Vector4(376,112,32,48), //blue teleporter
	Vector4(376,168,32,48), //green teleporter
	Vector4(144,256,64,64)  //Robot Home
};

GameMap::GameMap(const std::string& filename, std::vector<RigidBody*>& objects, Pathing& pathing, TextureManager& texManager) {
	tileTexture = texManager.GetTexture("Colony.png");

	std::ifstream mapFile(Assets::DATADIR + filename);

	if (!mapFile) {
		std::cout << "GameMap can't be loaded in!" << std::endl;
		return;
	}

	mapFile >> mapWidth;
	mapFile >> mapHeight;

	MapNode* nodeArray = new MapNode[mapWidth * mapHeight];

	mapData = new MapTileType[mapWidth * mapHeight];

	const int TILE_WIDTH = 16;
	const char WALL_TILE = '1';
	const char ROUGH_TILE = '2';
	const char FLAT_TILE = '0';


	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int tileIndex = (y * mapWidth) + x;

			char type = 0;

			mapFile >> type;

			nodeArray[tileIndex].x = x;
			nodeArray[tileIndex].y = y;
			nodeArray[tileIndex].isTraversable = true;
			nodeArray[tileIndex].isClosed = false;

			if (type == FLAT_TILE) {
				nodeArray[tileIndex].cost = 0.5f;
			} else if (type == ROUGH_TILE) {
				nodeArray[tileIndex].cost = 0.65f;
			} else if (type == WALL_TILE) {
				WallTile* test = new WallTile(x * TILE_WIDTH, y * TILE_WIDTH);
			    objects.emplace_back(test);
				nodeArray[tileIndex].g = 10.0f;
				nodeArray[tileIndex].isTraversable = false;
				nodeArray[tileIndex].isClosed = true;
			}


			mapData[tileIndex] = (MapTileType)(type - 48);
		}
	}
	mapFile >> structureCount;

	structureData = new StructureData[structureCount];
	
	pathing.setGameMap(nodeArray, mapWidth, mapHeight, TILE_WIDTH);

	for (int i = 0; i < structureCount; ++i) {
		int type  = 0;
		int xTile = 0;
		int yTile = 0;

		mapFile >> type;
		mapFile >> xTile;
		mapFile >> yTile;

		structureData[i].structureType = (MapStructureType)type;
		structureData[i].startPos.x = xTile * 16;
		structureData[i].startPos.y = yTile * 16;
	}
}

GameMap::~GameMap()	{
	delete[] mapData;
	delete[] structureData;
}

void GameMap::DrawMap(GameSimsRenderer & r) {
	int tileSize = 16;

	srand(0); //so we get consistent floor tiles

	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int tileType = mapData[(y * mapWidth) + x];

			Vector4 tileData;

			if (tileType == MapTileType::Rough) {
				int randomFlatTile = rand() % 4;
				tileData = randomRoughTiles[randomFlatTile];
			} else {
				tileData = tileSpecs[tileType];
			}

			Vector2 texPos  = Vector2(tileData.x, tileData.y);
			Vector2 texSize = Vector2(tileData.z, tileData.w);

			Vector2 screenPos = Vector2(x * 16, y * 16);

			r.DrawTextureArea((OGLTexture*)tileTexture, texPos, texSize, screenPos, false);
		}
	}

	for (int i = 0; i < structureCount; ++i) {
		Vector4 buildingData = buildingTypes[structureData[i].structureType];

		Vector2 texPos = Vector2(buildingData.x, buildingData.y);
		Vector2 texSize = Vector2(buildingData.z, buildingData.w);

		Vector2 screenPos = structureData[i].startPos;

		r.DrawTextureArea((OGLTexture*)tileTexture, texPos, texSize, screenPos, false);
	}
}