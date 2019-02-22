/******************************************************************************
Class:Vector2
Implements:
Author:Rich Davison
Description:VERY simple Vector2 class. Students are encouraged to modify 
this as necessary!


-_-_-_-_-_-_-_,------,
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""

*//////////////////////////////////////////////////////////////////////////////
#pragma once
#include <iostream>

namespace NCL {
	namespace Maths {
		class Vector2 {

		public:
			Vector2(void) {
				ToZero();
			}

			Vector2(const float x, const float y) {
				this->x = x;
				this->y = y;
			}

			~Vector2(void) {}

			float x;
			float y;

			void ToZero() {
				x = 0.0f;
				y = 0.0f;
			}

			float magnitude() {
				return sqrtf(x * x + y * y);
			}

			void normalize() {
				bool x0 = negl(x);
				bool y0 = negl(y);

				if (x0 && !y0) {
					x = 0.0f;
					y = y > 0 ? 1.0f : -1.0f;

					return;
				}
				
				if (y0 && !x0) {
					x = x > 0 ? 1.0f : -1.0f;
					y = 0.0f;

					return;
				}
				
				if (y0 && x0) {
					x = 0.0f;
					y = 0.0f;

					return;
				}

				float mag = magnitude();
					
				x = x / mag;
				y = y / mag;
			}

			inline friend std::ostream& operator<<(std::ostream& o, const Vector2& v) {
				o << "Vector2(" << v.x << "," << v.y << ")" << std::endl;
				return o;
			}

			inline Vector2  operator-(const Vector2  &a) const {
				return Vector2(x - a.x, y - a.y);
			}

			inline Vector2  operator+(const Vector2  &a) const {
				return Vector2(x + a.x, y + a.y);
			}

			inline Vector2  operator/(const Vector2  &a) const {
				return Vector2(x / a.x, y / a.y);
			};

			inline Vector2  operator*(float f) const {
				return Vector2(x * f, y * f);
			};

			inline Vector2  operator/(float f) const {
				return Vector2(x / f, y / f);
			};

			inline void operator+=(const Vector2  &a) {
				x += a.x;
				y += a.y;
			}

			inline void operator-=(const Vector2  &a) {
				x -= a.x;
				y -= a.y;
			}

			inline void operator*=(float f) {
				x *= f;
				y *= f;
			}

			inline void operator/=(float f) {
				x /= f;
				y /= f;
			}

		private:
			bool negl(float f) {
				const float small = 0.000001f;
				return f > -small && f < small;
			}
		};
	}
}
