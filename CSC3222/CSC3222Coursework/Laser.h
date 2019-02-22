#pragma once
#include "SimObject.h"

namespace NCL {
	namespace CSC3222 {
		class Laser : public SimObject {
		private:
		    Vector2 FIRE_DIR;
			const float SPEED = 100.0f;
			const float ACCELERATION = 300.0f;

			float test = 0.0f;

		public:
			Laser(Vector2& direction);
			~Laser();

			void DrawObject(GameSimsRenderer &r) override;
			bool UpdateObject(float dt) override;
		};
	}
}

