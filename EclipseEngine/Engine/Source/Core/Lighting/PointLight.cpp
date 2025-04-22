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

	Math::Vec3 PointLight::GetPosition()
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->GetPosition();
	}
}