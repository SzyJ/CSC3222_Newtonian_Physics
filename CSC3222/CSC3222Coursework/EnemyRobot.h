#pragma once
#include "Robot.h"
#include "Pathing.h"

namespace NCL {
	namespace CSC3222 {
		enum EnemyRobotState {
			stunned,
			following,
			patrolling
		};
		class EnemyRobot : public Robot {
		public:
			EnemyRobot();
			~EnemyRobot();

			bool UpdateObject(float dt) override;
			void setPathing(Pathing path);
			void setPlayerPosition(Vector2* playerPos);

		protected:
			EnemyRobotState state;

			void OnCollision(RigidBody* otherBody) override;
			void followingState();
			void patrollingState();

			float	thinkTime;
			bool	moving;

			float speed;

			Pathing path;
			Vector2* playerPosition;

			int followedNodes;
			float stunnedTime = 0.0f;

			const float STUN_TIME = 0.07f;
		};
	}
}

