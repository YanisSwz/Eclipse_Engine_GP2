#include "Lighting/DirectionalLight.hpp"
#include "GameObject.hpp"

namespace Core
{
	meta::factory<DirectionalLight> DirectionalLight::factory = meta::reflect<DirectionalLight>(hash("DirectionalLight"))
		.data<&DirectionalLight::SetActive, &DirectionalLight::IsActive>(hash("IsActive"));
		//.data<&DirectionalLight::SetColor, &DirectionalLight::GetColor>(hash("Color"));

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

	void DirectionalLight::Serialize(json& _j)
	{
		Math::Vec4 color = GetColor();

		_j["DirectionalLight"] = json{
				{"IsActive", IsActive()},
				{"Color", { color.w, color.x, color.y, color.z }}
		};
	}

	void DirectionalLight::Deserialize(const json& _j)
	{
		bool bIsActive;
		float color[4];

		_j.at("IsActive").get_to(bIsActive);
		_j.at("Color").get_to(color);

		SetActive(bIsActive);
		SetColor(color[1], color[2], color[3], color[0]);
	}
}