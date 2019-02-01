#include "Robot.h"
#include "GameSimsRenderer.h"

using namespace NCL;
using namespace CSC3222;

int  startY[] = { 0,32,64,64 };
int  startX[] = { 0,16,32,48 };
bool flips[]  = { false,false,false,true };

Robot::Robot() : SimObject()	{
	currentAnimDir		= Left;
	currentanimFrame	= 0;
}

Robot::~Robot()	{

}

void Robot::DrawObject(GameSimsRenderer &r) {
	//determine frame of anim to play, and whether its flipped or not

	Vector2 screenPos = position;

	Vector2 texPos;

	Vector2 texSize = Vector2(16, 32);

	texPos.x = startX[currentanimFrame];
	texPos.y = startY[currentAnimDir];

	r.DrawTextureArea((OGLTexture*)texture, texPos, texSize, screenPos, flips[currentAnimDir]);

}

void Robot::UpdateAnimFrame(float dt) {
	frameTime -= dt;

	if (frameTime < 0) {
		currentanimFrame = (currentanimFrame + 1) % 4;
		frameTime += 1.0f / 12.0f;
	}
}
