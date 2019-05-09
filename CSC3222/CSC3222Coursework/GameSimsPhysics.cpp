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
			CollisionResolution collider = body1Collider->collidesWithTest(body2Collider);

			if (body1Collider->collidesWith(body2Collider)) {
				handleCollision(body1, body2, collider);
			}
		}

		for (RigidBody* body2 : staticBodies) {
			CollisionVolume* body2Collider = body2->GetCollider();
			CollisionResolution collider = body1Collider->collidesWithTest(body2Collider);
			
			if (body1Collider->collidesWith(body2Collider)) {
				handleCollision(body1, body2, collider);
			}
		}
	}
}

void GameSimsPhysics::handleCollision(RigidBody* body1, RigidBody* body2, const CollisionResolution& collision) {
	body1->OnCollision(body2);
	body2->OnCollision(body1);

	r->DrawString("X", body1->GetPosition());
	
	float body1Mass = body1->inverseMass;
	float body2Mass = body2->inverseMass;
	float totalMass = body1Mass + body2Mass;

	NCL::Maths::Vector2 normal = collision.getNormal();

	NCL::Maths::Vector2 posChangeVector = normal * collision.getPenetration();

	body1->ChangePosition(posChangeVector * (body1Mass / totalMass));
	body2->ChangePosition(posChangeVector * -1 * (body2Mass / totalMass));

	float body1E = body1->getElasticty();
	float body2E = body2->getElasticty();
	
	NCL::Maths::Vector2 body1Velocity = body1->GetVelocity();
	NCL::Maths::Vector2 body2Velocity = body2->GetVelocity();

	float body1VelDotProduct = body1Velocity.dot(normal);
	float body2VelDotProduct = body2Velocity.dot(normal);
	
	std::cout << "vel1 dot norml: " << body1VelDotProduct << std::endl;
	std::cout << "vel2 dot norml: " << body2VelDotProduct << std::endl;

	NCL::Maths::Vector2 body1ReflectedVelocity = body1Velocity - (normal * (2.0f * body1VelDotProduct));
	NCL::Maths::Vector2 body2ReflectedVelocity = body2Velocity - (normal * (2.0f * body2VelDotProduct));
	body1->SetVelocity(body1ReflectedVelocity * body1E);
	body2->SetVelocity(body2ReflectedVelocity * body2E);



}