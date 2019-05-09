#include "EnemyRobot.h"
#include "TextureManager.h"
#include "../../Common/TextureLoader.h"
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

EnemyRobot::EnemyRobot() : Robot()	{
	texture = texManager->GetTexture("Turret Bot overgrown.png");

	moving = false;

	SetCollider(new CollisionVolume(Shape::Circle, 16.0f, &position, COLLISION_X_OFFSET, COLLISION_Y_OFFSET));
}

EnemyRobot::~EnemyRobot()	{
}

void EnemyRobot::setPathing(Pathing path) {
	this->path = path;
	this->path.resetMapInstance();
}

void EnemyRobot::setPlayerPosition(Vector2* playerPos) {
	playerPosition = playerPos;
}

bool EnemyRobot::UpdateObject(float dt) {
	thinkTime -= dt;
	if (moving) {
		position += velocity * dt;
		UpdateAnimFrame(dt);
	}

	if (thinkTime < 0) {
		moving		= false;
		velocity	= Vector2();

		thinkTime += 0.5f;

		float testSpeed = 16;

		
		Vector2 direction = path.getDirection(position.x, position.y, playerPosition->x, playerPosition->y);
		direction -= position;
		direction.normalize();
		velocity = direction * testSpeed;

		/*
		int choice = rand() % 5;

		if (choice == 1) {
			moving = true;
			velocity.x = -testSpeed;
			currentAnimDir = MovementDir::Left;
		}

		if (choice == 2) {
			moving = true;
			velocity.x = testSpeed;
			currentAnimDir = MovementDir::Right;
		}

		if (choice == 3) {
			moving = true;
			velocity.y = -testSpeed;
			currentAnimDir = MovementDir::Up;
		}

		if (choice == 4) {
			moving = true;
			velocity.y = testSpeed;
			currentAnimDir = MovementDir::Down;
		}*/
	}

	return true;
}
