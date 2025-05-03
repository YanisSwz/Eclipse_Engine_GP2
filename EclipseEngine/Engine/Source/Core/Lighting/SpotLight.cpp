#include "Lighting/SpotLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	SpotLight::SpotLight()
	{
	}

	SpotLight::~SpotLight()
	{
	}

	RHI::SpotLightData SpotLight::GetData() const
	{
		return RHI::SpotLightData{
			m_color,
			GetPosition(),
			cosf(Math::Tools::ToRad(m_innerCutOff/2.f)),
			GetDirection(),
			cosf(Math::Tools::ToRad(m_outerCutOff/2.f)),
			m_constantAttenuation,
			1.f / m_distance,
			1.f / (m_distance * m_distance),
			0.f
		};
	}

	Math::Vec3 SpotLight::GetPosition() const
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->GetPosition();
	}

	Math::Vec3 SpotLight::GetDirection() const
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->GetForward();
	}
}