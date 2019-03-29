#pragma once

#include "../../Common/Vector2.h"
#include "CollisionResolution.h"

namespace NCL {
	namespace CSC3222 {
		enum Shape {
			Square, Circle
		};

		class CollisionVolume {
		private:
			const Shape shape;
			const float width;
			const NCL::Maths::Vector2* position;

			void* onCollision;

			const float X_OFFSET;
            const float Y_OFFSET;

			static bool squareCircleCollision(const CollisionVolume& square, const CollisionVolume& circle);
			static bool circleCircleCollision(const CollisionVolume& thisCircle, const CollisionVolume& otherCircle);
			static bool squareSquareCollision(const CollisionVolume& thisSquare, const CollisionVolume& otherSquare);

			static CollisionResolution testCCCol(const CollisionVolume& thisSquare, const CollisionVolume& otherSquare);

		public:
			CollisionVolume(Shape shape, float width, NCL::Maths::Vector2* pos, float xOffset = 0, float yOffset = 0);
			~CollisionVolume();

			bool collidesWith(const CollisionVolume* other);
			CollisionResolution collidesWithTest(const CollisionVolume* other);

			const Shape getShape() const;
			const float getWidth() const;
			const NCL::Maths::Vector2* getPosition() const;
			const float getXOffset() const;
			const float getYOffset() const;
		};
	}
}

