#include <string>
#include "GameSimsPhysics.h"
#include "RigidBody.h"
#include "CollisionVolume.h"
#include "../../Common/Vector2.h"
#include "GameSimsRenderer.h"

using namespace NCL;
using namespace CSC3222;

GameSimsPhysics::GameSimsPhysics()	{

}

GameSimsPhysics::~GameSimsPhysics()	{

}

void GameSimsPhysics::Update(float dt) {
	Integration(dt);
	CollisionDetection(dt);
}

void GameSimsPhysics::AddRigidBody(RigidBody* b) {
	if (b->isStatic()) {
	    staticBodies.emplace_back(b);
	} else {
	    dynamicBodies.emplace_back(b);
	}
}

void GameSimsPhysics::RemoveRigidBody(RigidBody* b) {
	if (b->isStatic()) {
        auto at = std::find(staticBodies.begin(), staticBodies.end(), b);

        if (at != staticBodies.end()) {
            //maybe delete too?
            // delete b; ??
            staticBodies.erase(at);
        }
	} else {
        auto at = std::find(dynamicBodies.begin(), dynamicBodies.end(), b);

        if (at != dynamicBodies.end()) {
            //maybe delete too?
            // delete b; ??
            dynamicBodies.erase(at);
        }
	}
}

void GameSimsPhysics::Integration(float dt) {
	for (RigidBody* body : dynamicBodies) {
		Vector2 accel = body->force * body->inverseMass;
		body->velocity += accel * dt * SLOWDOWN_FACTOR;
		body->position += body->velocity * dt;
	}
}

void GameSimsPhysics::CollisionDetection(float dt) {
	int dynamicBodyCount = dynamicBodies.size();

	for (int thisIndex = 0; thisIndex < dynamicBodyCount; ++thisIndex) {
		RigidBody* body1 = dynamicBodies[thisIndex];
		CollisionVolume* body1Collider = body1->GetCollider();

		for (int otherIndex = thisIndex + 1; otherIndex < dynamicBodyCount; ++otherIndex) {
			RigidBody* body2 = dynamicBodies[otherIndex];
			CollisionVolume* body2Collider = body2->GetCollider();

			if (body1Collider->collidesWith(body2Collider)) {
				body1->OnCollision(body2);
				body2->OnCollision(body1);

				r->DrawString("X", body1->GetPosition());
			}
		}

		for (RigidBody*  body2 : staticBodies) {
			CollisionVolume* body2Collider = body2->GetCollider();

			if (body1Collider->collidesWith(body2Collider)) {
				body1->OnCollision(body2);
				body2->OnCollision(body1);

				r->DrawString("X", body1->GetPosition());
			}
		}

	}
}