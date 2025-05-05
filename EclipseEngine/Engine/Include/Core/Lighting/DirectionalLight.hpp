#pragma once
#include "ProjectExports.hpp"
#include "Lighting/ILight.hpp"
#include "RHIInterfaces/Lights.hpp"

namespace Core
{
	class DirectionalLight : public ILight
	{
	public:
		static meta::factory<DirectionalLight> factory;

		ECLIPSE_ENGINE DirectionalLight() = default;
		ECLIPSE_ENGINE ~DirectionalLight() = default;

		ECLIPSE_ENGINE RHI::DirLightData GetData() const;

	private:
		Math::Vec3 GetDirection() const;
	};

	void to_json(json& _j, const DirectionalLight& _dirLight);
	void from_json(const json& _j, DirectionalLight& _dirLight);
}