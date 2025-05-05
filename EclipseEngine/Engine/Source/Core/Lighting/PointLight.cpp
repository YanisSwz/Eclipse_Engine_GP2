#include "Lighting/PointLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	meta::factory<PointLight> PointLight::factory = meta::reflect<PointLight>(hash("PointLight"))
		.data<&PointLight::SetActive, &PointLight::IsActive>(hash("IsActive"))
		//.data<&PointLight::SetColor, &PointLight::GetColor>(hash("Color"))
		.data<&PointLight::m_constantAttenuation>(hash("ConstantAttenuation"))
		.data<&PointLight::m_linearAttenuation>(hash("LinearAttenuation"))
		.data<&PointLight::m_quadraticAttenuation>(hash("QuadraticAttenuation"));

	RHI::PointLightData PointLight::GetData() const
	{
		return RHI::PointLightData{
			m_color,
			GetPosition(),
			m_constantAttenuation,
			1.f/m_distance,
			1.f/(m_distance * m_distance),
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

	void to_json(json& _j, const PointLight& _pointLight)
	{
		Math::Vec4 color = _pointLight.GetColor();

		_j = json{
			{"IsActive", _pointLight.IsActive()},
			{"Color", { color.w, color.x, color.y, color.z }},
			{"Distance", _pointLight.GetDistance()},
			{"ConstantAttenuation", _pointLight.GetConstAtt()},
			{"LinearAttenuation", _pointLight.GetLinAtt()},
			{"QuadraticAttenuation", _pointLight.GetQuadAtt()}
		};
	}

	void from_json(const json& _j, PointLight& _pointLight)
	{
		bool bIsActive;
		float color[4];
		float distance;
		float constAtt;
		float linAtt;
		float quadAtt;

		_j.at("IsActive").get_to(bIsActive);
		_j.at("Color").get_to(color);
		_j.at("Distance").get_to(distance);
		_j.at("ConstantAttenuation").get_to(constAtt);
		_j.at("LinearAttenuation").get_to(linAtt);
		_j.at("QuadraticAttenuation").get_to(quadAtt);

		_pointLight.SetActive(bIsActive);
		_pointLight.SetColor(color[0], color[1], color[2], color[3]);
		_pointLight.SetDistance(distance);
		_pointLight.SetConstAtt(constAtt);
		_pointLight.SetLinAtt(linAtt);
		_pointLight.SetQuadAtt(quadAtt);
	}
}