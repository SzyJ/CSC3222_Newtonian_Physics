#include "GameMap.h"
#include "GameSimsRenderer.h"
#include "TextureManager.h"
#include "../../Common/Assets.h"
#include "../../Common/TextureLoader.h"
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


GameMap::GameMap(const std::string& filename, std::vector<SimObject*>& objects, TextureManager& texManager)	{
	tileTexture = texManager.GetTexture("Colony.png");

	std::ifstream mapFile(Assets::DATADIR + filename);

	if (!mapFile) {
		std::cout << "GameMap can't be loaded in!" << std::endl;
		return;
	}

	mapFile >> mapWidth;
	mapFile >> mapHeight;

	mapData = new MapTileType[mapWidth * mapHeight];

	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int tileIndex = (y * mapWidth) + x;

			char type = 0;

			mapFile >> type;

			mapData[tileIndex] = (MapTileType)(type - 48);
		}
	}
	mapFile >> structureCount;

	structureData = new StructureData[structureCount];

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
			}
			else {
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