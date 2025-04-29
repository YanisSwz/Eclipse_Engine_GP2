#pragma once
#include "ProjectExports.hpp"
#include "Lighting/ILight.hpp"
#include "RHIInterfaces/Lights.hpp"
#include "meta/factory.hpp"
#include <string>

namespace Core
{
	class SpotLight : public ILight
	{
	public:
		static meta::factory<SpotLight> factory;

		ECLIPSE_ENGINE SpotLight() = default;
		ECLIPSE_ENGINE ~SpotLight() = default;

		ECLIPSE_ENGINE RHI::SpotLightData GetData() const;

	private:
		inline static std::hash<std::string_view> m_hash{};

		float m_innerCutOff = 0.91f;
		float m_outerCutOff = 0.82f;
		float m_constantAttenuation = 1.f;
		float m_linearAttenuation = 0.09f;
		float m_quadraticAttenuation = 0.032f;

		Math::Vec3 GetPosition() const;
		Math::Vec3 GetDirection() const;
	};
}