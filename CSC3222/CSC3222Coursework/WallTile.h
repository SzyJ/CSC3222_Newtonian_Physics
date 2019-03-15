#pragma once
#include "SimObject.h"
#include "../../Common/Vector2.h"

namespace NCL {
    namespace CSC3222 {
        class WallTile : public SimObject {
        public:
            WallTile(Vector2* pos);
            ~WallTile();

            void DrawObject(GameSimsRenderer &r) override;
            bool UpdateObject(float dt) override;
        };
    }
}