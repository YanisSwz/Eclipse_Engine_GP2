#include "Lighting/SpotLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	meta::factory<SpotLight> SpotLight::factory = meta::reflect<SpotLight>(hash("SpotLight"))
		.data<&SpotLight::SetActive, &SpotLight::IsActive>(hash("IsActive"))
		//.data<&SpotLight::SetColor, &SpotLight::GetColor>(hash("Color"))
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
			cosf(Math::Tools::ToRad(m_innerCutOff/2.f)),
			GetDirection(),
			cosf(Math::Tools::ToRad(m_outerCutOff/2.f)),
			m_constantAttenuation,
			1.f / m_distance,
			1.f / (m_distance * m_distance),
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

	void SpotLight::Serialize(json& _j)
	{
		Math::Vec4 color = GetColor();

		_j = json{
			{"IsActive", IsActive()},
			{"Color", { color.w, color.x, color.y, color.z }},
			{"InnerCutOff", GetInnerCutOff()},
			{"OuterCutOff", GetOuterCutOff()},
			{"Distance", GetDistance()},
			{"ConstantAttenuation", GetConstAtt()},
			{"LinearAttenuation", GetLinAtt()},
			{"QuadraticAttenuation", GetQuadAtt()}
		};
	}

	void SpotLight::Deserialize(const json& _j)
	{
		bool bIsActive;
		float color[4];
		float innerCutOff;
		float outerCutOff;
		float distance;
		float constAtt;
		float linAtt;
		float quadAtt;

		_j.at("IsActive").get_to(bIsActive);
		_j.at("Color").get_to(color);
		_j.at("InnerCutOff").get_to(innerCutOff);
		_j.at("OuterCutOff").get_to(outerCutOff);
		_j.at("Distance").get_to(distance);
		_j.at("ConstantAttenuation").get_to(constAtt);
		_j.at("LinearAttenuation").get_to(linAtt);
		_j.at("QuadraticAttenuation").get_to(quadAtt);

		SetActive(bIsActive);
		SetColor(color[0], color[1], color[2], color[3]);
		SetInnerCutOff(innerCutOff);
		SetOuterCutOff(outerCutOff);
		SetDistance(distance);
		SetConstAtt(constAtt);
		SetLinAtt(linAtt);
		SetQuadAtt(quadAtt);
	}
}