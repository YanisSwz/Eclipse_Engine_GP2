#pragma once
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace RHI
{
	struct DirLightData
	{
		Math::Vec4 color;
		Math::Vec3 dir;		
	};

	struct PointLightData
	{
		Math::Vec4 color;
		Math::Vec3 pos;
		float constAttenuation;
		float linAttenuation;
		float quadAttenuation;
	};

	struct SpotLightData
	{
		Math::Vec4 color;
		Math::Vec3 pos;
		Math::Vec3 dir;
		float innerCutOff;
		float outerCutOff;
		float constAttenuation;
		float linAttenuation;
		float quadAttenuation;
	};
}