#include "Lighting/DirectionalLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	meta::factory<DirectionalLight> DirectionalLight::factory = meta::reflect<DirectionalLight>(m_hash("DirectionalLight"))
		.data<&DirectionalLight::SetActive, &DirectionalLight::IsActive>(m_hash("IsActive"))
		.data<&DirectionalLight::SetColor, &DirectionalLight::GetColor>(m_hash("Color"));

	RHI::DirLightData DirectionalLight::GetData() const
	{
		return RHI::DirLightData{
			m_color,
			GetDirection(),
			0.f
		};
	}

	Math::Vec3 DirectionalLight::GetDirection() const
	{
		if (m_gameObject == nullptr)
			return Math::Vec3();
		return m_gameObject->transform->GetForward();
	}
}