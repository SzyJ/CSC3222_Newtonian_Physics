#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include <vector>

namespace NCL {
	namespace CSC3222 {
		class SimObject;
		class GameSimsRenderer : public OGLRenderer	{
		public:
			GameSimsRenderer();
			virtual ~GameSimsRenderer();

			void AddSimObject(const SimObject* s) const;
			void RemoveSimObject(const SimObject* s);

			void Update(float dt) override;

			void DrawTextureArea(OGLTexture* texture, Vector2 start, Vector2 size, Vector2 screenPos, bool invertX = false);

			void SetScreenProperties(int tileSize, int numTilesX, int numTilesY);
		protected:
			void RenderFrame()	override;

			struct TextureArea {
				OGLTexture* texture;
				Vector2 start;
				Vector2 size;
				Vector2 screenPos;
				bool	flipX;
			};

			int tileSize;
			int numTilesX;
			int numTilesY;

			std::vector<SimObject*> allObjects;

			std::vector<TextureArea> texAreas;

			OGLShader*	spriteShader;
			OGLMesh*	spriteMesh;
		};
	}
}

