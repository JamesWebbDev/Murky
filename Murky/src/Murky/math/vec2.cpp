#include "mkpch.h"

#include "vec2.h"
#include "maths.h"

namespace Murky
{
	float Vec2::Magnitude(const Vec2& v)
	{
		return (float)sqrt(v.x * v.x + v.y * v.y);
	}

	float Vec2::SqrMagnitude(const Vec2& v)
	{
		return v.x * v.x + v.y * v.y;
	}

	Vec2 Vec2::Normalise(const Vec2& v)
	{
		float magnitude = Magnitude(v);
		return magnitude > 0 ? v / magnitude : v;
	}

	Vec2 Vec2::NewNormalise(const Vec2& v)
	{
		float min = Vec2::Min(v);
		Vec2 max = Vec2::Max(v);
		Vec2 result = 2;
		return result;
	}

	float Vec2::Min(const Vec2& v)
	{
		return v.x < v.y ? v.x : v.y;
	}

	float Vec2::Max(const Vec2& v)
	{
		return v.x > v.y ? v.x : v.y;
	}

	Vec2 Vec2::Max(const Vec2& v1, const Vec2& v2)
	{
		Vec2 result = Vec2();

		result.x = v1.x > v2.x ? v1.x : v2.x;
		result.y = v1.y > v2.y ? v1.y : v2.y;

		return result;
	}

	Vec2 Vec2::Abs(const Vec2& v)
	{
		float x = v.x > 0 ? v.x : v.x * -1;
		float y = v.y > 0 ? v.y : v.y * -1;
		return Vec2(x, y);
	}

	float Vec2::Dot(const Vec2& v1, const Vec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	Vec2 Vec2::Reflect(const Vec2& inDirection, const Vec2& inNormal)
	{
		float num = -2.0f * Dot(inNormal, inDirection);
		return Vec2(num * inNormal.x + inDirection.x, num * inNormal.y + inDirection.y);
	}

	Vec2 Vec2::FlipY(const Vec2& v)
	{
		return Vec2(v.x, v.y * -1);
	}

	float Vec2::Area(const Vec2& v)
	{
		return v.x * v.y;
	}

	float Vec2::CrossProduct(const Vec2& a, const Vec2& b)
	{
		return a.x * b.y - a.y * b.x;
	}

	Vec2 Vec2::CrossProduct(const Vec2& a, float s)
	{
		return Vec2(s * a.y, -s * a.x);
	}

	Vec2 Vec2::CrossProduct(float s, const Vec2& a)
	{
		return Vec2(-s * a.y, s * a.x);
	}
}
