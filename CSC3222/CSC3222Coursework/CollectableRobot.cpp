#include "CollectableRobot.h"
#include "GameSimsRenderer.h"
#include "TextureManager.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector4.h"
#include "CollisionVolume.h"
#include "PlayerRobot.h"

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

Vector2* CollectableRobot::nextFollow;

Vector4 spriteDetails[5] = {
	Vector4(40 ,174,16, 18),
	Vector4(72 ,174,16, 18),
	Vector4(104,174,16, 18),
	Vector4(136,174,16, 18),
	Vector4(17 ,51 ,14, 13)
};

CollectableRobot::CollectableRobot() : SimObject()	{
	collected = false;
	inverseMass = 1.0f / 0.5f;
	int r = rand() % 5;
	type = (RobotType)r;

	if (type == Special) {
		texture = texManager->GetTexture("Green Bot Sprites.png");
	}
	else {
		texture = texManager->GetTexture("Gum Bot Sprites.png");
	}

	SetCollider(new CollisionVolume(Shape::Circle, 16.0f, &position, 0, 2));
}

CollectableRobot::CollectableRobot(RobotType type) : CollectableRobot() {
	this->type = type;
}

CollectableRobot::~CollectableRobot()	{

}

void CollectableRobot::DrawObject(GameSimsRenderer &r) {
	Vector2 texPos(spriteDetails[type].x, spriteDetails[type].y);
	Vector2 texSize(spriteDetails[type].z, spriteDetails[type].w);

	Vector2 screenPos = position;

	r.DrawTextureArea((OGLTexture*)texture, texPos, texSize, screenPos, false);

	//r.DrawString("c", Vector2(screenPos.x + 8, screenPos.y + 8 + 2));
}

bool CollectableRobot::UpdateObject(float dt) {
	if (collected) {
		float force = (SNAPPINESS * FOLLOW_DISTANCE) - (DAMPENING_CONSTANT * SPRING_AXIS_VELOCITY);

		Vector2 direction = *following - position;
		direction.normalize();

		velocity = direction * force;
	}
	else {
		//they should just sit still
	}
	return true;
}

void CollectableRobot::OnCollision(RigidBody* otherBody) {
	if (collected) {
		return;
	}
	
	if (typeid(*otherBody).name() == typeid(PlayerRobot).name()) {
		std::cout << "Player!!! YEEET" << std::endl;
		collected = true;
		following = nextFollow;
		updateNextFollow();
	}
}

void CollectableRobot::updateNextFollow() {
	nextFollow = &position;
}

void CollectableRobot::setNextFollow(Vector2* nextFollow) {
	this->nextFollow = nextFollow;
}