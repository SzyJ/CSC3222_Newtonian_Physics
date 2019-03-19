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
	allBodies.emplace_back(b);
}

void GameSimsPhysics::RemoveRigidBody(RigidBody* b) {
	auto at = std::find(allBodies.begin(), allBodies.end(), b);

	if (at != allBodies.end()) {
		//maybe delete too?
		// delete b; ??
		allBodies.erase(at);
	}
}

void GameSimsPhysics::Integration(float dt) {
	for (RigidBody* body : allBodies) {
		Vector2 accel = body->force * body->inverseMass;
		body->velocity += accel * dt * SLOWDOWN_FACOTR;
		body->position += body->velocity * dt;

	}
}

void GameSimsPhysics::CollisionDetection(float dt) {
	for (int i = 0; i < allBodies.size(); ++i) {
        RigidBody* body1 = allBodies[i];
        CollisionVolume* body1Collider = body1->GetCollider();

		for (int j = i + 1; j < allBodies.size(); ++j) {
            RigidBody* body2 = allBodies[j];
            CollisionVolume* body2Collider = body2->GetCollider();

            if (body1Collider->collidesWith(body2Collider)) {

				body1->OnCollision(body2);
				body2->OnCollision(body1);

				r->DrawString("X", allBodies[i]->GetPosition());
				//std::cout << "Hit (" << std::to_string(allColliders[i]->getShape()) << ", " << std::to_string(allColliders[j]->getShape()) << ")" << std::endl;
			}
		}
	}
}