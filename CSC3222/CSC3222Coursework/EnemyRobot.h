#pragma once
#include "Robot.h"
#include "Pathing.h"

namespace NCL {
	namespace CSC3222 {
		class EnemyRobot : public Robot {

		public:
			EnemyRobot();
			~EnemyRobot();

			bool UpdateObject(float dt) override;
			void setPathing(Pathing path);
			void setPlayerPosition(Vector2* playerPos);

		protected:
			float	thinkTime;
			bool	moving;

			Pathing path;
			Vector2* playerPosition;
		};
	}
}

