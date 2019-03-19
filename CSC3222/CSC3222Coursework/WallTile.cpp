#pragma once
#include "WallTile.h"
#include "CollisionVolume.h"

using namespace NCL;
using namespace CSC3222;

WallTile::WallTile(Vector2* pos) : RigidBody() {
    SetCollider(new CollisionVolume(Shape::Square, 16.0f, pos));
}

WallTile::~WallTile() {}


void WallTile::OnCollision(RigidBody* otherBody) {
    // If something has to happen to the wall on collision, implement here.
}