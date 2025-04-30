#include "Lighting/PointLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	meta::factory<PointLight> PointLight::factory = meta::reflect<PointLight>(hash("PointLight"))
		.data<&PointLight::SetActive, &PointLight::IsActive>(m_hash("IsActive"))
		.data<&PointLight::SetColor, &PointLight::GetColor>(m_hash("Color"))
		.data<&PointLight::m_constantAttenuation>(m_hash("ConstantAttenuation"))
		.data<&PointLight::m_linearAttenuation>(m_hash("LinearAttenuation"))
		.data<&PointLight::m_quadraticAttenuation>(m_hash("QuadraticAttenuation"));

	RHI::PointLightData PointLight::GetData() const
	{
		return RHI::PointLightData{
			m_color,
			GetPosition(),
			m_constantAttenuation,
			m_linearAttenuation,
			m_quadraticAttenuation,
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