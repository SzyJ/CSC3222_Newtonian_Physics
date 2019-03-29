#pragma once

#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3222 {
		struct CollisionResolution {
			float penetration;
			NCL::Maths::Vector2 collisionNormal;

			CollisionResolution(float pen, NCL::Maths::Vector2 normal)
				: penetration(pen), collisionNormal(normal) {}

			static CollisionResolution NoCollision() {
				return CollisionResolution(0, NCL::Maths::Vector2(0, 0));
			}

			void setNormal(NCL::Maths::Vector2 newNormal);
			NCL::Maths::Vector2 getNormal() const;

			void setPenetration(float newPen);
			float getPenetration() const;
		};
	}
}