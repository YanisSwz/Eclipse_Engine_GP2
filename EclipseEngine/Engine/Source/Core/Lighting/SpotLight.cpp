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

	Math::Vec3 SpotLight::GetPosition()
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->position;
	}

	Math::Vec3 SpotLight::GetDirection()
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->forward;
	}
}