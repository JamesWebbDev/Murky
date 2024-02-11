#ifndef MK_VEC2_INT_H
#define MK_VEC2_INT_H

#include "../core/core.h"

namespace Murky
{
	struct MURKY_API Vec2Int
	{
		Vec2Int(const int value = 0.0f) :
			x(value),
			y(value) {}

		Vec2Int(const int x, const int y) :
			x(x),
			y(y) {}


		int x;
		int y;

		static Vec2Int  Zero() { return Vec2Int(0); }
		static Vec2Int  Up() { return Vec2Int(0, 1); }
		static Vec2Int  Down() { return Vec2Int(0, -1); }
		static Vec2Int  Left() { return Vec2Int(-1, 0); }
		static Vec2Int  Right() { return Vec2Int(1, 0); }

		static float Magnitude(const Vec2Int& v);
		static float SqrMagnitude(const Vec2Int& v);
		static Vec2Int  Normalise(const Vec2Int& v);
		static Vec2Int  NewNormalise(const Vec2Int& v);
		static float Min(const Vec2Int& v);
		static float Max(const Vec2Int& v);
		static Vec2Int  Max(const Vec2Int& v1, const Vec2Int& v2);
		static Vec2Int  Abs(const Vec2Int& v);
		static float Dot(const Vec2Int& v1, const Vec2Int& v2);
		static Vec2Int  Reflect(const Vec2Int& inNormal, const Vec2Int& inDirection);
		static Vec2Int  FlipY(const Vec2Int& v);
		static int Area(const Vec2Int& v);
		// Two crossed vectors return a scalar
		static int CrossProduct(const Vec2Int& a, const Vec2Int& b);
		// More exotic (but necessary) forms of the cross product 
		// with a vector a and scalar s, both returning a vector
		static Vec2Int CrossProduct(const Vec2Int& a, float s);
		static Vec2Int CrossProduct(float s, const Vec2Int& a);

		static std::string ToString(const Vec2Int& v);

		bool operator==(const Vec2Int& v) const
		{
			return (x == v.x && y == v.y);
		}

		Vec2Int operator+(const Vec2Int& v) const
		{
			return Vec2Int(x + v.x, y + v.y);
		}

		Vec2Int operator-(const Vec2Int& v) const
		{
			return Vec2Int(x - v.x, y - v.y);
		}

		Vec2Int operator*(const Vec2Int& v) const
		{
			return Vec2Int(x * v.x, y * v.y);
		}

		Vec2Int operator/(const Vec2Int& v) const
		{
			return Vec2Int(x / v.x, y / v.y);
		}

		Vec2Int operator*(const float value) const
		{
			return Vec2Int(x * (int)value, y * (int)value);
		}

		Vec2Int operator/(const float value) const
		{
			return Vec2Int(x / (int)value, y / (int)value);
		}

		Vec2Int& operator=(const Vec2Int& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		Vec2Int& operator+=(const Vec2Int& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vec2Int& operator-=(const Vec2Int& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		Vec2Int& operator*=(const Vec2Int& v)
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}

		Vec2Int& operator/=(const Vec2Int& v)
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}
	};
}

#endif
