#pragma once
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace RHI
{
	struct DirLightData
	{
		Math::Vec4 color;
		Math::Vec3 dir;
		float padding;
	};

	struct PointLightData
	{
		Math::Vec4 color;
		Math::Vec3 pos;
		float constAttenuation;
		float linAttenuation;
		float quadAttenuation;
		float padding1;
		float padding2;
	};

	struct SpotLightData
	{
		Math::Vec4 color;
		Math::Vec3 pos;
		float innerCutOff;
		Math::Vec3 dir;
		float outerCutOff;
		float constAttenuation;
		float linAttenuation;
		float quadAttenuation;
		float padding;
	};
}