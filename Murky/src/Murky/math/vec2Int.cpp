#include "mkpch.h"

#include "vec2Int.h"
#include "maths.h"

namespace Murky
{
	float Vec2Int::Magnitude(const Vec2Int& v)
	{
		return (float)sqrt(v.x * v.x + v.y * v.y);
	}

	float Vec2Int::SqrMagnitude(const Vec2Int& v)
	{
		return (float)(v.x * v.x + v.y * v.y);
	}

	Vec2Int Vec2Int::Normalise(const Vec2Int& v)
	{
		float magnitude = Magnitude(v);
		return magnitude > 0 ? v / magnitude : v;
	}

	Vec2Int Vec2Int::NewNormalise(const Vec2Int& v)
	{
		float min = Vec2Int::Min(v);
		Vec2Int max = Vec2Int::Max(v);
		Vec2Int result = 2;
		return result;
	}

	float Vec2Int::Min(const Vec2Int& v)
	{
		return (float)(v.x < v.y ? v.x : v.y);
	}

	float Vec2Int::Max(const Vec2Int& v)
	{
		return (float)(v.x > v.y ? v.x : v.y);
	}

	Vec2Int Vec2Int::Max(const Vec2Int& v1, const Vec2Int& v2)
	{
		Vec2Int result = Vec2Int();

		result.x = v1.x > v2.x ? v1.x : v2.x;
		result.y = v1.y > v2.y ? v1.y : v2.y;

		return result;
	}

	Vec2Int Vec2Int::Abs(const Vec2Int& v)
	{
		int x = v.x > 0 ? v.x : v.x * -1;
		int y = v.y > 0 ? v.y : v.y * -1;
		return Vec2Int(x, y);
	}

	float Vec2Int::Dot(const Vec2Int& v1, const Vec2Int& v2)
	{
		return (float)(v1.x * v2.x + v1.y * v2.y);
	}

	Vec2Int Vec2Int::Reflect(const Vec2Int& inDirection, const Vec2Int& inNormal)
	{
		float num = -2.0f * Dot(inNormal, inDirection);
		return Vec2Int(num * inNormal.x + inDirection.x, num * inNormal.y + inDirection.y);
	}

	Vec2Int Vec2Int::FlipY(const Vec2Int& v)
	{
		return Vec2Int(v.x, v.y * -1);
	}

	int Vec2Int::Area(const Vec2Int& v)
	{
		return v.x * v.y;
	}

	int Vec2Int::CrossProduct(const Vec2Int& a, const Vec2Int& b)
	{
		return a.x * b.y - a.y * b.x;
	}

	Vec2Int Vec2Int::CrossProduct(const Vec2Int& a, float s)
	{
		return Vec2Int(s * a.y, -s * a.x);
	}

	Vec2Int Vec2Int::CrossProduct(float s, const Vec2Int& a)
	{
		return Vec2Int(-s * a.y, s * a.x);
	}

	std::string Vec2Int::ToString(const Vec2Int& v)
	{
		return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
	}
}
