#include "SimObject.h"
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;

TextureManager*  SimObject::texManager = nullptr;
RobotRescueGame* SimObject::game = nullptr;

SimObject::SimObject()	{
	texture		= nullptr;
	collider	= nullptr;
}

SimObject::~SimObject()	{
	std::cout << "simobj destructor" << std::endl;
	delete collider;
}

void SimObject::InitObjects(RobotRescueGame* game, TextureManager* texManager) {
	SimObject::game			= game;
	SimObject::texManager	= texManager;
}

void SimObject::OnCollision(RigidBody* otherBody) {
    // TODO: Do Collision Resolution
}