#pragma once
#include <random>

namespace Math
{
	namespace Tools
	{
		constexpr const float PI = 3.141592653f;
		constexpr const float epsilon = 0.00001f; //std::numeric_limits<float>::epsilon();

		inline float ToDeg(float f) { return f * (180.f / PI); }
		inline float ToRad(float f) { return f * (PI / 180.f); }
		inline float Lerp(float a, float b, float f) { return a + (b - a) * f; }
		inline int Sign(float f) 
		{
			if (f < epsilon)
				return -1;
			else if (f > epsilon)
				return 1;
			else
				return 0;
		}
		/// <summary>
		/// Return a random value between 0 and 1
		/// </summary>
		/// <returns>float</returns>
		inline float Random() { return static_cast<float>(std::rand()) / RAND_MAX; }
	}
}