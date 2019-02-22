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

			Vector2(const Vector2& other) {
				this->x = other.x;
				this->y = other.y;
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

			Vector2* normalize() {
				bool x0 = negl(x);
				bool y0 = negl(y);

				if (x0 && !y0) {
					x = 0.0f;
					y = y > 0 ? 1.0f : -1.0f;

					return this;
				}
				
				if (y0 && !x0) {
					x = x > 0 ? 1.0f : -1.0f;
					y = 0.0f;

					return this;
				}
				
				if (y0 && x0) {
					x = 0.0f;
					y = 0.0f;

					return this;
				}

				float mag = magnitude();
					
				x = x / mag;
				y = y / mag;

				return this;
			}

			Vector2 getNormalized() {
				Vector2 copy(x, y);
				return *copy.normalize();
			}

			float getAngle(bool clockwise = true) {
			    if (clockwise) {
                    return atan2(y, x);
			    } else {
                    return atan2(x, y);
			    }

			}

			Vector2 getAbsolute() {
			    Vector2 copy(abs(x), abs(y));
			    return copy;
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
