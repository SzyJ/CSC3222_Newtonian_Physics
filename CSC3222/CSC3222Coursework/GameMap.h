#pragma once
#include <string>
#include <vector>

#include "../../Common/Vector2.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"

namespace NCL {
	namespace Rendering {
		class TextureBase;
	}
	using namespace Maths;
	namespace CSC3222 {
		class GameSimsRenderer;
		class SimObject;
		class TextureManager;

		enum MapTileType {
			Flat,
			Wall,
			Rough,
			MAX_TILES
		};

		enum MapStructureType {
			RedTeleporter,
			GreenTeleporter,
			BlueTeleporter
		};

		struct StructureData {
			Vector2				startPos;
			MapStructureType	structureType;
		};

		class GameMap	{
		public:
			GameMap(const std::string& filename, std::vector<SimObject*>& objects, TextureManager& texManager);
			~GameMap();

			void DrawMap(GameSimsRenderer & r);

			int GetMapWidth() const {
				return mapWidth;
			}

			int GetMapHeight() const {
				return mapHeight;
			}

		protected:
			int mapWidth;
			int mapHeight;
			int structureCount;

			static Vector4 tileSpecs[MAX_TILES];

			Rendering::TextureBase*	tileTexture;
			MapTileType*	mapData;
			StructureData*	structureData;		
		};
	}
}

