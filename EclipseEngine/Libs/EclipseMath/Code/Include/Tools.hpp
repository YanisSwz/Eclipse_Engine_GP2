#pragma once

namespace Math
{
	namespace Tools
	{
		constexpr const float PI = 3.141592653f;
		constexpr const float epsilon = 0.00001f; //std::numeric_limits<float>::epsilon();

		inline float ToDeg(float f) { return f * (180.f / PI); }
		inline float ToRad(float f) { return f * (PI / 180.f); }
		inline float Lerp(float a, float b, float f) { return a + (b - a) * f; }
	}
}