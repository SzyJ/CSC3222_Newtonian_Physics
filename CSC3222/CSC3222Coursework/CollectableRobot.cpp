#include "CollectableRobot.h"
#include "GameSimsRenderer.h"
#include "TextureManager.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector4.h"

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

Vector4 spriteDetails[5] = {
	Vector4(40 ,174,16, 18),
	Vector4(72 ,174,16, 18),
	Vector4(104,174,16, 18),
	Vector4(136,174,16, 18),
	Vector4(17 ,51 ,14, 13)
};

CollectableRobot::CollectableRobot() : SimObject()	{
	collected = false;

	int r = rand() % 5;
	type = (RobotType)r;

	if (type == Special) {
		texture = texManager->GetTexture("Green Bot Sprites.png");
	}
	else {
		texture = texManager->GetTexture("Gum Bot Sprites.png");
	}
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
}

bool CollectableRobot::UpdateObject(float dt) {
	if (collected) {
		//they should follow the player!
	}
	else {
		//they should just sit still
	}
	return true;
}