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

		protected:
			RobotType type;

			bool	collected;
			Vector2 spawnPoint;
		};
	}
}

