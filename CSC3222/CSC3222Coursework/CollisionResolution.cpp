#include "CollisionResolution.h"

using namespace NCL;
using namespace CSC3222;

void CollisionResolution::setNormal(NCL::Maths::Vector2 newNormal) {
	collisionNormal = newNormal;
}

NCL::Maths::Vector2 CollisionResolution::getNormal() const {
	return collisionNormal;
}

void CollisionResolution::setPenetration(float newPen) {
	penetration = newPen;
}

float CollisionResolution::getPenetration() const {
	return penetration;
}