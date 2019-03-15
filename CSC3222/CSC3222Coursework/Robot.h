#pragma once
#include "SimObject.h"

namespace NCL {
	namespace CSC3222 {	
		class Robot :	public SimObject	{
		public:
			Robot();
			~Robot();

			void DrawObject(GameSimsRenderer &r) override;

		protected:		
			enum MovementDir {
				Up,
				Down,
				Left,
				Right
			};

			const float COLLISION_X_OFFSET = 0;
			const float COLLISION_Y_OFFSET = 16;

			void UpdateAnimFrame(float dt);

			MovementDir currentAnimDir;
			int			currentanimFrame;
			float		frameTime;
		};
	}
}

