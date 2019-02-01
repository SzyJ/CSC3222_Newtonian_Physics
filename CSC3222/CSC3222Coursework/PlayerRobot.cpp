#include "PlayerRobot.h"
#include "Laser.h"
#include "TextureManager.h"
#include "RobotRescueGame.h"
#include "../../Common/Window.h"

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

PlayerRobot::PlayerRobot() : Robot()	{
	texture = texManager->GetTexture("Turret Bot.png");

	position = Vector2(32, 32);
}

PlayerRobot::~PlayerRobot()	{

}

bool PlayerRobot::UpdateObject(float dt) {
	float testSpeed = 64;

	Vector2 newVelocity;

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT)) {
		currentAnimDir = MovementDir::Left;
		UpdateAnimFrame(dt);

		newVelocity.x = -testSpeed * dt;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT)) {
		currentAnimDir = MovementDir::Right;
		UpdateAnimFrame(dt);

		newVelocity.x = testSpeed * dt;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_UP)) {
		currentAnimDir = MovementDir::Up;
		UpdateAnimFrame(dt);

		newVelocity.y = -testSpeed * dt;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_DOWN)) {
		currentAnimDir = MovementDir::Down;
		UpdateAnimFrame(dt);

		newVelocity.y = testSpeed * dt;
	}

	position += newVelocity;

	if (Window::GetKeyboard()->KeyPressed(KEYBOARD_SPACE)) {
		Vector2 laserSpeed = newVelocity * 150.0f;
		Laser* shot = new Laser(laserSpeed);
		shot->SetPosition(position + Vector2(8,16));

		game->AddNewObject(shot);
	}

	return true;
}