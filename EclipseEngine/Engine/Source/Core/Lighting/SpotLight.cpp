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
			m_innerCutOff,
			GetDirection(),
			m_outerCutOff,
			m_constantAttenuation,
			m_linearAttenuation,
			m_quadraticAttenuation,
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