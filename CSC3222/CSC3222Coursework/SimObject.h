#pragma once
#include "../../Common/Vector2.h"
#include "RigidBody.h"

namespace NCL {
	using namespace Maths;
	namespace Rendering {
		class TextureBase;
	}
	namespace CSC3222 {
		class GameSimsRenderer;
		class TextureManager;
		class RobotRescueGame;
		class RigidBody;
		class CollisionVolume;

		class SimObject	: public RigidBody {
		public:
			SimObject();
			~SimObject();

			virtual bool UpdateObject(float dt) = 0;

			virtual void DrawObject(GameSimsRenderer &r) = 0;



			static void InitObjects(RobotRescueGame* game, TextureManager* manager);

		protected:
			Rendering::TextureBase* texture;

			static TextureManager*  texManager;
			static RobotRescueGame* game;


			virtual void OnCollision(RigidBody* otherBody) override;
		};
	}
}