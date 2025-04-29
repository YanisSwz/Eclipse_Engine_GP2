#include "Lighting/DirectionalLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	meta::factory<DirectionalLight> DirectionalLight::factory = meta::reflect<DirectionalLight>(m_hash("DirectionalLight"))
		.func<&DirectionalLight::IsActive>(m_hash("GetActive"))
		.func<&DirectionalLight::GetColor>(m_hash("GetColor"))
		.func<&DirectionalLight::SetActive>(m_hash("SetActive"))
		.func<&DirectionalLight::SetColor>(m_hash("SetColor"));

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