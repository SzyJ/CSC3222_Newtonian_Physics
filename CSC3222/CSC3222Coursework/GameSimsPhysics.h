#pragma once
#include <vector>
#include "../../Common/Vector2.h"
#include "CollisionResolution.h"
#include "GameSimsRenderer.h"

namespace NCL {
	namespace CSC3222 {
		class RigidBody;
		class CollisionVolume;

		class GameSimsPhysics {
		public:
			GameSimsRenderer* r;

		 	GameSimsPhysics();
			GameSimsPhysics(GameSimsRenderer* r)
				:r(r) {}
			~GameSimsPhysics();

			void Update(float dt);

			void AddRigidBody(RigidBody* b);
			void RemoveRigidBody(RigidBody* b);

		protected:
			void Integration(float dt);
			void CollisionDetection(float dt);

            std::vector<RigidBody*> dynamicBodies;
            std::vector<RigidBody*> staticBodies;

		private:
			const float SLOWDOWN_FACTOR = 0.99999999f;

			void handleCollision(RigidBody* body1, RigidBody* body2, const CollisionResolution& collision);
		};
	}
}

