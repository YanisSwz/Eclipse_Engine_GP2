#pragma once
#include "ProjectExports.hpp"
#include "Lighting/ILight.hpp"
#include "RHIInterfaces/Lights.hpp"
#include "meta/factory.hpp"

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
		static std::hash<std::string_view> m_hash;

		Math::Vec3 GetDirection() const;
	};
}