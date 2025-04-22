#pragma once
#include "ProjectExports.hpp"
#include "Lighting/ILight.hpp"
#include "RHIInterfaces/Lights.hpp"

namespace Core
{
	class DirectionalLight : public ILight
	{
	public:
		ECLIPSE_ENGINE DirectionalLight();
		ECLIPSE_ENGINE ~DirectionalLight();

		ECLIPSE_ENGINE RHI::DirLightData GetData() const;

	private:
		Math::Vec3 GetDirection() const;
	};
}