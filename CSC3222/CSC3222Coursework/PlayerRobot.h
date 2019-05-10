#pragma once
#include "Robot.h"
#include "CollectableRobot.h"

namespace NCL {
	namespace CSC3222 {
		class PlayerRobot : public Robot	{
		public:
			PlayerRobot();
			~PlayerRobot();

			bool UpdateObject(float dt) override;
			Vector2* getPlayerPositionVector();


		protected:
			void OnCollision(RigidBody* otherBody) override;

			CollectableRobot* lastRobot = nullptr;
		};
	}
}
