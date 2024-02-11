#include "mkpch.h"

#include "maths.h"

#include <cmath>

namespace Murky
{
	float Maths::Min(float a, float b)
	{
		return b < a ? b : a;
	}

	int Maths::Min(int a, int b)
	{
		return b < a ? b : a;
	}

	float Maths::Max(float a, float b)
	{
		return b > a ? b : a;
	}

	int Maths::Max(int a, int b)
	{
		return b > a ? b : a;
	}

	float Maths::Clamp(float value, float min, float max)
	{
		value = value < min ? min : value;
		value = value > max ? max : value;
		return value;
	}

	int Maths::Clamp(int value, int min, int max)
	{
		value = value < min ? min : value;
		value = value > max ? max : value;
		return value;
	}

	float Maths::Sqrt(const float value)
	{
		return std::sqrt(value);
	}

	float Maths::Abs(const float value)
	{
		return std::abs(value);
	}

	int Maths::Abs(const int value)
	{
		return std::abs(value);
	}

	float Maths::PythagoreanSolve(const float& v1, const float& v2)
	{
		float cSqr = (v1 * v1) + (v2 * v2);
		return std::sqrt(cSqr);
	}
}
