#pragma once
#include "WallTile.h"
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;

WallTile::WallTile(float x, float y) : RigidBody() {
    position.x = x;
    position.y = y;
    SetCollider(new CollisionVolume(Shape::Square, 16.0f, &position));
    makeStatic();
}

WallTile::~WallTile() {}


void WallTile::OnCollision(RigidBody* otherBody) {
    // If something has to happen to the wall on collision, implement here.
}