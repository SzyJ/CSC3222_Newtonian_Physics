#include <string>
#include "GameSimsPhysics.h"
#include "RigidBody.h"
#include "CollisionVolume.h"
#include "../../Common/Vector2.h"

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
		allBodies.erase(at);
	}
}

void GameSimsPhysics::AddCollider(CollisionVolume* c) {
	allColliders.emplace_back(c);
}

void GameSimsPhysics::RemoveCollider(CollisionVolume* c) {
	auto at = std::find(allColliders.begin(), allColliders.end(), c);

	if (at != allColliders.end()) {
		//maybe delete too?
		allColliders.erase(at);
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
    for(int i = 0; i < allColliders.size(); ++i) {
        for(int j = i + 1; j < allColliders.size(); ++j) {
            if (allColliders[i]->collidesWith(allColliders[j])) {
            	// Do Something
            	std::cout << "Hit (" << std::to_string(allColliders[i]->getShape()) << ", " << std::to_string(allColliders[j]->getShape()) << ")" << std::endl;
            }
        }
    }
}