#ifndef MK_VEC2_H
#define MK_VEC2_H

#include "../core/core.h"

namespace Murky
{
	struct MURKY_API Vec2
	{
		Vec2(const float value = 0.0f) :
			x(value),
			y(value) {}

		Vec2(const float x, const float y) :
			x(x),
			y(y) {}

		float x;
		float y;

		static Vec2  Zero() { return Vec2(0.0f); }

		static float Magnitude(const Vec2& v);
		static float SqrMagnitude(const Vec2& v);
		static Vec2  Normalise(const Vec2& v);
		static Vec2  NewNormalise(const Vec2& v);
		static float Min(const Vec2& v);
		static float Max(const Vec2& v);
		static Vec2  Max(const Vec2& v1, const Vec2& v2);
		static Vec2  Abs(const Vec2& v);
		static float Dot(const Vec2& v1, const Vec2& v2);
		static Vec2  Reflect(const Vec2& inNormal, const Vec2& inDirection);
		static Vec2  FlipY(const Vec2& v);
		static float Area(const Vec2& v);
		// Two crossed vectors return a scalar
		static float CrossProduct(const Vec2& a, const Vec2& b);
		// More exotic (but necessary) forms of the cross product 
		// with a vector a and scalar s, both returning a vector
		static Vec2  CrossProduct(const Vec2& a, float s);
		static Vec2  CrossProduct(float s, const Vec2& a);

		bool operator==(const Vec2& v) const
		{
			return (x == v.x && y == v.y);
		}

		Vec2 operator+(const Vec2& v) const
		{
			return Vec2(x + v.x, y + v.y);
		}

		Vec2 operator-(const Vec2& v) const
		{
			return Vec2(x - v.x, y - v.y);
		}

		Vec2 operator*(const Vec2& v) const
		{
			return Vec2(x * v.x, y * v.y);
		}

		Vec2 operator/(const Vec2& v) const
		{
			return Vec2(x / v.x, y / v.y);
		}

		Vec2 operator*(const float value) const
		{
			return Vec2(x * value, y * value);
		}

		Vec2 operator/(const float value) const
		{
			return Vec2(x / value, y / value);
		}

		Vec2& operator=(const Vec2& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		Vec2& operator+=(const Vec2& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vec2& operator-=(const Vec2& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		Vec2& operator*=(const Vec2& v)
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}

		Vec2& operator/=(const Vec2& v)
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}
	};
}

#endif