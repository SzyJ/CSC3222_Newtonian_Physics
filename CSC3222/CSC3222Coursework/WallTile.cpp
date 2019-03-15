#pragma once
#include "WallTile.h"
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;

WallTile::WallTile(Vector2* pos) : SimObject() {
    SetCollider(new CollisionVolume(Shape::Square, 16.0f, pos));
}

WallTile::~WallTile() {}

void WallTile::DrawObject(GameSimsRenderer &r) {}

bool WallTile::UpdateObject(float dt) { return true; }