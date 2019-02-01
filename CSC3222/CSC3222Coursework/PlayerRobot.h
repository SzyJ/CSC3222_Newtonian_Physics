#pragma once
#include "Robot.h"

namespace NCL {
	namespace CSC3222 {
		class PlayerRobot : public Robot	{
		public:
			PlayerRobot();
			~PlayerRobot();

			bool UpdateObject(float dt) override;
		};
	}
}

