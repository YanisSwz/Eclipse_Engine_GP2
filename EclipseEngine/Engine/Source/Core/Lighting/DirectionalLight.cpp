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

	void to_json(json& _j, const DirectionalLight& _dirLight)
	{
		Math::Vec4 color = _dirLight.GetColor();

		_j = json{
			{"IsActive", _dirLight.IsActive()},
			{"Color", { color.w, color.x, color.y, color.z }}
		};
	}

	void from_json(const json& _j, DirectionalLight& _dirLight)
	{
		bool bIsActive;
		float color[4];

		_j.at("IsActive").get_to(bIsActive);
		_j.at("Color").get_to(color);

		_dirLight.SetActive(bIsActive);
		_dirLight.SetColor(color[0], color[1], color[2], color[3]);
	}
}