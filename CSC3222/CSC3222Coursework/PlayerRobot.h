#pragma once
#include "Robot.h"
#include "CollectableRobot.h"

namespace NCL {
	namespace CSC3222 {
		enum statusEffects {
			blue,
			red,
			green,
			pink
		};

		class PlayerRobot : public Robot	{
		public:
			PlayerRobot();
			~PlayerRobot();

			bool UpdateObject(float dt) override;
			Vector2* getPlayerPositionVector();

			void applyBlueStatus();
			void applyRedStatus();
			void applyGreenStatus();
			void applyPinkStatus();

		protected:
			bool blueStatus = false;
			bool redStatus = false;
			bool greenStatus = false;
			bool pinkStatus = false;


			void OnCollision(RigidBody* otherBody) override;

			void depositAllRobots(bool applyStatus);
		};
	}
}
