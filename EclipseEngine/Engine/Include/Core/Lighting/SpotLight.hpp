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

	private:
		float m_innerCutOff = 0.91f;
		float m_outerCutOff = 0.82f;
		float m_constantAttenuation = 1.f;
		float m_linearAttenuation = 0.09f;
		float m_quadraticAttenuation = 0.032f;

		Math::Vec3 GetPosition() const;
		Math::Vec3 GetDirection() const;
	};
}