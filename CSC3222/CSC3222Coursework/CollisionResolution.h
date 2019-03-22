#pragma once

#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3222 {
		struct CollisionResolution {
			float penetration;
			Vector2 collisionNormal;
		};
	}
}