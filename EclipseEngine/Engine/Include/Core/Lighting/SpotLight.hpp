#pragma once
#include "ProjectExports.hpp"
#include "Lighting/ILight.hpp"
#include "RHIInterfaces/Lights.hpp"

namespace Core
{
	class SpotLight : public ILight
	{
	public:
		ECLIPSE_ENGINE SpotLight();
		ECLIPSE_ENGINE ~SpotLight();

		ECLIPSE_ENGINE RHI::SpotLightData GetData() const;
		ECLIPSE_ENGINE inline float& GetInnerCutoffRef() { return m_innerCutOff; };
		ECLIPSE_ENGINE inline float& GetOuterCutoffRef() { return m_outerCutOff; };
		ECLIPSE_ENGINE inline float GetInnerCutoff() { return m_innerCutOff; };
		ECLIPSE_ENGINE inline float GetOuterCutoff() { return m_outerCutOff; };

		ECLIPSE_ENGINE inline float& GetDistanceRef() { return m_distance; };
		ECLIPSE_ENGINE inline float GetDistance() { return m_distance; };
	private:
		/// <summary>
		/// Inner cutoff angle in degrees
		/// </summary>
		float m_innerCutOff = 25.f;
		/// <summary>
		/// Inner cutoff angle in degrees
		/// </summary>
		float m_outerCutOff = 35.f;
		float m_constantAttenuation = 1.f;
		float m_linearAttenuation = 0.09f;
		float m_quadraticAttenuation = 0.032f;
		float m_distance = 10.f;

		Math::Vec3 GetPosition() const;
		Math::Vec3 GetDirection() const;
	};
}