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

	Math::Vec3 DirectionalLight::GetDirection()
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->GetForward();
	}
}