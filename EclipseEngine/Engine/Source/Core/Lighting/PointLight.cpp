#include "Lighting/PointLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	PointLight::PointLight()
	{
	}

	PointLight::~PointLight()
	{
	}

	RHI::PointLightData PointLight::GetData() const
	{
		return RHI::PointLightData{
			m_color,
			GetPosition(),
			m_constantAttenuation,
			m_linearAttenuation,
			m_quadraticAttenuation
		};
	}

	Math::Vec3 PointLight::GetPosition() const
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->GetPosition();
	}
}