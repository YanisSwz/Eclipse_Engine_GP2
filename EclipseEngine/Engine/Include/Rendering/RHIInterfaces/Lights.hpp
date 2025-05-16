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

	struct LightsData
	{
		Math::Vec4 ambientLight;
		DirLightData dirLightsData[100];
		PointLightData pointLightsData[100];
		SpotLightData spotLightsData[100];
		int dirLightsNb;
		int pointLightsNb;
		int spotLightsNb;
		int padding;

		LightsData(Math::Vec4 _ambient, std::vector<DirLightData> _dirLightsData, std::vector<PointLightData> _pointLightsData, std::vector<SpotLightData> _spotLightsData, int _dirLightsNb, int _pointLightsNb, int _spotLightsNb, int _padding = 0)
			:ambientLight(_ambient), dirLightsNb(_dirLightsNb), pointLightsNb(_pointLightsNb), spotLightsNb(_spotLightsNb), padding(_padding)
		{
			for (int i = 0; i < _dirLightsNb; ++i)
				dirLightsData[i] = _dirLightsData[i];
			for (int i = 0; i < _pointLightsNb; ++i)
				pointLightsData[i] = _pointLightsData[i];
			for (int i = 0; i < _spotLightsNb; ++i)
				spotLightsData[i] = _spotLightsData[i];
		}
	};
}