#pragma once
#include "../../Common/Vector2.h"
#include "CollisionVolume.h"

namespace NCL {
	using namespace Maths;
	namespace CSC3222 {
		class RigidBody	{
			friend class GameSimsPhysics;
		public:
			RigidBody();
			virtual ~RigidBody();


            void SetCollider(CollisionVolume * c) {
                collider = c;
            }

            CollisionVolume* GetCollider() const {
                return collider;
            }

            Vector2 GetPosition() const {
				return position;
			}

			void SetPosition(const Vector2& newPosition) {
				position = newPosition;
			}

			void ChangePosition(const Vector2& diffPosition) {
				position += diffPosition;
			}

			Vector2 GetVelocity() const {
				return velocity;
			}

			void SetVelocity(const Vector2& newVelocity) {
				velocity = newVelocity;
			}
			
			void SetVelocity(const float xVal, const float yVal) {
				velocity.x = xVal;
				velocity.y = yVal;
			}

			void AddForce(const Vector2& newForce) {
				force += newForce;
			}

			void makeStatic() {
                isStaticObj = true;
            }

            void makeDynamic() {
                isStaticObj = false;
            }

            bool isStatic() {
                return isStaticObj;
            }

			float getElasticty() {
				return elasticity;
			}


		protected:
            CollisionVolume* collider;

			Vector2 position;
			Vector2 velocity;
			Vector2 force;

			float inverseMass;
			float elasticity;

            virtual void OnCollision(RigidBody* otherBody) = 0;

		private:
		    bool isStaticObj = false;
        };
	}
}
