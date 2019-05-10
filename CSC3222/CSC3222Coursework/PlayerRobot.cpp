#include "PlayerRobot.h"
#include "Laser.h"
#include "TextureManager.h"
#include "RobotRescueGame.h"
#include "../../Common/Window.h"
#include "CollisionVolume.h"
#include "BuildingLocations.h"

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

PlayerRobot::PlayerRobot() : Robot()	{
	texture = texManager->GetTexture("Turret Bot.png");

	position = Vector2(32, 32);
	inverseMass = 1.0f / 5.0f;
	SetCollider(new CollisionVolume(Shape::Circle, 16.0f, &position, COLLISION_X_OFFSET, COLLISION_Y_OFFSET));

	GetCollider()->definePlayer();
}

PlayerRobot::~PlayerRobot()	{

}

Vector2* PlayerRobot::getPlayerPositionVector() {
	return &position;
}
bool PlayerRobot::UpdateObject(float dt) {
	float testSpeed = 128;

	// Calculate Direction
	Vector2 newVelocity;
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		currentAnimDir = MovementDir::Left;
		UpdateAnimFrame(dt);

		newVelocity.x = -1.0f;
	} else if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		currentAnimDir = MovementDir::Right;
		UpdateAnimFrame(dt);

		newVelocity.x = 1.0f;
	} else {
		newVelocity.x = 0.0f;
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		currentAnimDir = MovementDir::Up;
		UpdateAnimFrame(dt);	

		newVelocity.y = -1.0f;
	} else if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		currentAnimDir = MovementDir::Down;
		UpdateAnimFrame(dt);

		newVelocity.y = 1.0f;
	} else {
		newVelocity.y = 0.0f;
	}

	// Set speed
	newVelocity.normalize();
	newVelocity *= testSpeed * dt;

	//position += newVelocity;
	velocity = newVelocity * 50;
	//force = newVelocity;

	if (Window::GetKeyboard()->KeyPressed(KEYBOARD_SPACE)) {
		Vector2 laserSpeed = newVelocity * 150.0f;
		Laser* shot = new Laser(*(new Vector2(
		currentAnimDir == MovementDir::Left
			? -1 :
		currentAnimDir == MovementDir::Right
			? 1 : 0,
		currentAnimDir == MovementDir::Up
			? -1 :
		currentAnimDir == MovementDir::Down
			? 1 : 0)));
		shot->SetPosition(position + Vector2(COLLISION_X_OFFSET + 8, COLLISION_Y_OFFSET + 8));

		game->AddNewObject(shot);
	}

	if (position.x > HOME_LEFT && position.x < HOME_RIGHT &&
		position.y > HOME_UP   && position.y < HOME_DOWN) {
		depositAllRobots(true);
	}

	return true;
}

void PlayerRobot::applyBlueStatus() {
	blueStatus = true;
}

void PlayerRobot::applyRedStatus() {
	redStatus = true;
}

void PlayerRobot::applyGreenStatus() {
	greenStatus = true;
}

void PlayerRobot::applyPinkStatus() {
	pinkStatus = true;
}


void PlayerRobot::OnCollision(RigidBody* otherBody) {
	if (typeid(*otherBody).name() == typeid(Laser).name()) {
		depositAllRobots(false);
		blueStatus = false;
		redStatus = false;
		greenStatus = false;
		pinkStatus = false;
	}
}

void PlayerRobot::depositAllRobots(bool applyStatus) {
	CollectableRobot* nextFollow = CollectableRobot::getNextFollow();
	if (nextFollow == nullptr) {
		return;
	}

	for (CollectableRobot* bot = nextFollow; bot != nullptr; bot = bot->getFollowing()) {
		bot->markForDeletion();
		std::cout << "Add Score (100)!!" << std::endl;
		if (applyStatus) {
			if (bot->getRobotType()== RobotType::Freeze) {
				applyBlueStatus();
			} else if (bot->getRobotType() == RobotType::Speed) {
				applyRedStatus();
			} else if (bot->getRobotType() == RobotType::Score) {
				applyGreenStatus();
			} else if (bot->getRobotType() == RobotType::Armour) {
				applyPinkStatus();
			}
		}

		CollectableRobot::resetNextFollow();
	}
}