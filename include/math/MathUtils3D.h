#pragma once

#include <algorithm>

namespace Liar
{
	static const float ZERO_TO_LERANCE = 1e-6;
	static const float MAX_VALUE = 3.40282347e+38;
	static const float MIN_VALUE = -3.40282347e+38;

	class MathUtils3D
	{
	public:
		static bool IsZero(float v)
		{
			return abs(v) < ZERO_TO_LERANCE;
		}

		static bool NearEqual(float n1, float n2)
		{
			return IsZero(n1 - n2);
		}

		static float FastInvSqrt(float value)
		{
			if (IsZero(value))
			{
				return value;
			}
			else
			{
				return 1.0 / sqrtf(value);
			}
		}
	};

}