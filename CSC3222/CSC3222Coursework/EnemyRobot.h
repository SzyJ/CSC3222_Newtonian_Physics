#pragma once
#include "Robot.h"
#include "Pathing.h"

namespace NCL {
	namespace CSC3222 {
		enum EnemyRobotState {
			thinking,
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

			void followingState();
			void patrollingState();

			float	thinkTime;
			bool	moving;

			float speed;

			Pathing path;
			Vector2* playerPosition;

			int followedNodes;
		};
	}
}

