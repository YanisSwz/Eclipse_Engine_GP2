#include "Lighting/SpotLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	meta::factory<SpotLight> SpotLight::factory = meta::reflect<SpotLight>(hash("SpotLight"))
		.data<&SpotLight::SetActive, &SpotLight::IsActive>(hash("IsActive"))
		.data<&SpotLight::SetColor, &SpotLight::GetColor>(hash("Color"))
		.data<&SpotLight::m_innerCutOff>(hash("InnerCutoff"))
		.data<&SpotLight::m_outerCutOff>(hash("OuterCutoff"))
		.data<&SpotLight::m_constantAttenuation>(hash("ConstantAttenuation"))
		.data<&SpotLight::m_linearAttenuation>(hash("LinearAttenuation"))
		.data<&SpotLight::m_quadraticAttenuation>(hash("QuadraticAttenuation"));

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