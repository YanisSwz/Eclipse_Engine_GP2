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

		ECLIPSE_ENGINE void Serialize(json& _j) override;
		ECLIPSE_ENGINE void Deserialize(const json& _j) override;

	private:
		Math::Vec3 GetDirection() const;
	};
}