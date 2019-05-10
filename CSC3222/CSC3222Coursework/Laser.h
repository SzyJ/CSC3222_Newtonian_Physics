#pragma once
#include "SimObject.h"

namespace NCL {
	namespace CSC3222 {
		class Laser : public SimObject {
		private:
		    Vector2 FIRE_DIR;
		    const float INITIAL_VELOCITY =200.0f;
			const float FIRE_FORCE = 0.0f;
			const float MASS = 0.003f;
			 
			const int BOUNCE_THREASHOLD = 5;

			float test = 0.0f;
			

		protected:
			void OnCollision(RigidBody* otherBody) override;



		public:
			Laser(Vector2& direction);
			~Laser();

			int bounceCount = 0;

			void DrawObject(GameSimsRenderer &r) override;
			bool UpdateObject(float dt) override;

			int getBounceCount();
		};
	}
}

