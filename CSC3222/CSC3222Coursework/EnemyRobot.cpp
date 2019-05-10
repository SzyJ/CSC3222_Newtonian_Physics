#include "EnemyRobot.h"
#include "TextureManager.h"
#include "../../Common/TextureLoader.h"
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

EnemyRobot::EnemyRobot() : Robot()	{
	texture = texManager->GetTexture("Turret Bot overgrown.png");
	inverseMass = 1.0f / 1.0f;
	moving = false;

	SetCollider(new CollisionVolume(Shape::Circle, 16.0f, &position, COLLISION_X_OFFSET, COLLISION_Y_OFFSET));

	state = EnemyRobotState::thinking;
	speed = 32.0f;
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
		UpdateAnimFrame(dt);
	}

	if (thinkTime < 0) {
		moving		= false;
		velocity	= Vector2();

		thinkTime += 0.5f;

		float distFromPlayerAprox = abs(playerPosition->x - position.x) + abs(playerPosition->y - position.y);
		if (distFromPlayerAprox > 150.0f) {
			patrollingState();
		} else {
			followingState();
		}
		
	}

	return true;
}

void EnemyRobot::followingState() {
	Vector2 direction = path.getDirection(position.x + collider->getXOffset(), position.y + collider->getYOffset(), playerPosition->x + collider->getXOffset(), playerPosition->y + collider->getYOffset());
	path.resetMapInstance();
	direction.x -= collider->getXOffset();
	direction.y -= collider->getYOffset();

	direction -= position;
	direction.normalize();

	moving = true;
	if (abs(direction.x) > abs(direction.y)) {
		if (direction.x > 0) {
			currentAnimDir = MovementDir::Right;
		} else {
			currentAnimDir = MovementDir::Left;
		}
	} else {
		if (abs(direction.y) > 0) {
			currentAnimDir = MovementDir::Down;
		} else {
			currentAnimDir = MovementDir::Up;
		}
	}

	velocity = direction * speed;
}

void EnemyRobot::patrollingState() {

		int choice = rand() % 5;
		if (choice == 1) {
			moving = true;
			velocity.x = -speed;
			currentAnimDir = MovementDir::Left;
		}

		if (choice == 2) {
			moving = true;
			velocity.x = speed;
			currentAnimDir = MovementDir::Right;
		}

		if (choice == 3) {
			moving = true;
			velocity.y = -speed;
			currentAnimDir = MovementDir::Up;
		}

		if (choice == 4) {
			moving = true;
			velocity.y = speed;
			currentAnimDir = MovementDir::Down;
		}
}
