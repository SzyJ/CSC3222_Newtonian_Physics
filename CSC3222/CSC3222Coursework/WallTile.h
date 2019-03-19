#pragma once
#include "SimObject.h"
#include "../../Common/Vector2.h"

namespace NCL {
    namespace CSC3222 {
        class WallTile : public RigidBody {
        public:
            WallTile(Vector2* pos);
            ~WallTile();

        protected:
            virtual void OnCollision(RigidBody* otherBody) override;
        };
    }
}