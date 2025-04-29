#include "Lighting/SpotLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	meta::factory<SpotLight> SpotLight::factory = meta::reflect<SpotLight>(m_hash("SpotLight"))
		.func<&SpotLight::IsActive>(m_hash("GetActive"))
		.func<&SpotLight::GetColor>(m_hash("GetColor"))
		.func<&SpotLight::SetActive>(m_hash("SetActive"))
		.func<&SpotLight::SetColor>(m_hash("SetColor"))
		.data<&SpotLight::m_innerCutOff>(m_hash("InnerCutoff"))
		.data<&SpotLight::m_outerCutOff>(m_hash("OuterCutoff"))
		.data<&SpotLight::m_constantAttenuation>(m_hash("ConstantAttenuation"))
		.data<&SpotLight::m_linearAttenuation>(m_hash("LinearAttenuation"))
		.data<&SpotLight::m_quadraticAttenuation>(m_hash("QuadraticAttenuation"));

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