#include "PlayerRobot.h"
#include "Laser.h"
#include "TextureManager.h"
#include "RobotRescueGame.h"
#include "../../Common/Window.h"
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

PlayerRobot::PlayerRobot() : Robot()	{
	texture = texManager->GetTexture("Turret Bot.png");

	position = Vector2(32, 32);

	SetCollider(new CollisionVolume(Shape::Circle, 16.0f, &position, COLLISION_X_OFFSET, COLLISION_Y_OFFSET));
}

PlayerRobot::~PlayerRobot()	{

}

bool PlayerRobot::UpdateObject(float dt) {
	float testSpeed = 64;

	// Calculate Direction
	Vector2 newVelocity;
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		currentAnimDir = MovementDir::Left;
		UpdateAnimFrame(dt);

		newVelocity.x = -1.0f;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		currentAnimDir = MovementDir::Right;
		UpdateAnimFrame(dt);

		newVelocity.x = 1.0f;
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		currentAnimDir = MovementDir::Up;
		UpdateAnimFrame(dt);	

		newVelocity.y = -1.0f;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		currentAnimDir = MovementDir::Down;
		UpdateAnimFrame(dt);

		newVelocity.y = 1.0f;
	}

	// Set speed
	newVelocity.normalize();
	newVelocity *= testSpeed * dt;

	position += newVelocity;

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

	return true;
}