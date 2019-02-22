#include "Laser.h"
#include "TextureManager.h"
#include "GameSimsRenderer.h"

#include "../../Common/Maths.h"

#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"

using namespace NCL;
using namespace CSC3222;

Vector4 frames[16] = {
	Vector4(0, 36, 16 , 7), //9 o clock

	Vector4(1, 21, 16, 8),
	Vector4(3, 4, 13, 12),
	Vector4(22, 1, 8 ,15),
	Vector4(37, 1, 7 ,16), //12 0 clock

	Vector4(51,1, 8, 15),
	Vector4(65, 4 , 13 ,12),
	Vector4(65, 21, 15, 8),
	Vector4(65, 36, 16, 7),//3 o clock

	Vector4(65, 50, 15 , 8),
	Vector4(65, 63, 13, 12),
	Vector4(51, 63, 8, 15),
	Vector4(37, 63, 7 ,16), //6 o clock
	Vector4(22, 63 , 8, 15),
	Vector4(3, 63, 13 ,12),
	Vector4(1, 50, 15, 8)
};

Laser::Laser(Vector2& direction)
    : SimObject() {
	texture = texManager->GetTexture("bullet.png");

    Vector2 normalizedDir = direction.getNormalized();
	velocity = normalizedDir.getAbsolute() * SPEED;
	FIRE_DIR = normalizedDir;
}

Laser::~Laser()	{

}

void Laser::DrawObject(GameSimsRenderer &r) {
	Vector2 screenPos = position;
	Vector2 texPos;
	Vector2 texSize = Vector2(16, 16);

	float radAngle = FIRE_DIR.getAngle();
	radAngle += PI;
	radAngle *= 16.0f / (2 * PI);

	int frame = (int) radAngle % 16;

	texPos.x = frames[frame].x;
	texPos.y = frames[frame].y;

	texSize.x = frames[frame].z;
	texSize.y = frames[frame].w;

	r.DrawTextureArea((OGLTexture*)texture, texPos, texSize, screenPos);
}

bool Laser::UpdateObject(float dt) {
    // Using v = u + at
    velocity.x += ACCELERATION * dt;
    velocity.y += ACCELERATION * dt;

	// Using s = vt - 0.5at^2
    float xDisplacement = velocity.x * dt - (0.5f * ACCELERATION * dt * dt);
    float yDisplacement = velocity.y * dt - (0.5f * ACCELERATION * dt * dt);
    position.x += xDisplacement * FIRE_DIR.x;
    position.y += yDisplacement * FIRE_DIR.y;

	return true;
}
