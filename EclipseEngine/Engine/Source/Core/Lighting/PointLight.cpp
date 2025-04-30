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
			1.f/m_distance,
			1.f/(m_distance * m_distance),
			0.f,
			0.f
		};
	}

	Math::Vec3 PointLight::GetPosition() const
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->GetPosition();
	}
}