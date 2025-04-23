#include "Lighting/DirectionalLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	DirectionalLight::DirectionalLight()
	{
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	RHI::DirLightData DirectionalLight::GetData() const
	{
		return RHI::DirLightData{
			m_color,
			GetDirection()
		};
	}

	Math::Vec3 DirectionalLight::GetDirection() const
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->GetForward();
	}
}