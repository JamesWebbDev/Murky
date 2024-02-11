#ifndef MK_MATHS_H
#define MK_MATHS_H

#include "../core/core.h"

#include <math.h>

namespace Murky
{
	struct MURKY_API Maths
	{
		static float Min(float a, float b);
		static int   Min(int a, int b);
		static float Max(float a, float b);
		static int   Max(int a, int b);
		static float Clamp(float value, const float min, const float max);
		static int   Clamp(int value, const int min, const int max);
		static float Sqrt(const float value);
		static float Abs(const float value);
		static int   Abs(const int value);
		static float PythagoreanSolve(const float& v1, const float& v2);
	};
}

#endif