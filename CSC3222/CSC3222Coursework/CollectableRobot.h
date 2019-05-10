#pragma once
#include "SimObject.h"

namespace NCL {
	namespace CSC3222 {
		enum RobotType {
			Score,
			Speed,
			Armour,
			Freeze,
			Special
		};

		class CollectableRobot : public SimObject {
		public:
			CollectableRobot();
			CollectableRobot(RobotType type);
			~CollectableRobot();

			void DrawObject(GameSimsRenderer &r) override;
			bool UpdateObject(float dt) override;
			void OnCollision(RigidBody* otherBody) override;

			void setPlayerPos(Vector2* nextFollow);
			void updateNextFollow();

		protected:
			RobotType type;

			const float FOLLOW_DISTANCE = 5.0f;
			const float SNAPPINESS = 15.0f;

			const float DAMPENING_CONSTANT = 5.0f;
			const float SPRING_AXIS_VELOCITY = 1.0f;

			Vector2* playerPos;
			static CollectableRobot* nextFollow;
			CollectableRobot* following = nullptr;

			bool	collected;
			Vector2 spawnPoint;

			void depositAllRobots();
		};
	}
}

