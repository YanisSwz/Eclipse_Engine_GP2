#pragma once
#include "ProjectExports.hpp"
#include "Lighting/ILight.hpp"
#include "RHIInterfaces/Lights.hpp"

namespace Core
{
	class PointLight : public ILight
	{
	public:
		ECLIPSE_ENGINE PointLight();
		ECLIPSE_ENGINE ~PointLight();

		ECLIPSE_ENGINE RHI::PointLightData GetData() const;

	private:
		float m_constantAttenuation = 1.f;
		float m_linearAttenuation = 0.09f;
		float m_quadraticAttenuation = 0.032f;

		Math::Vec3 GetPosition() const;
	};
}