#pragma once
#include "ProjectExports.hpp"
#include "Lighting/ILight.hpp"

namespace Core
{
	class DirectionalLight : public ILight
	{
	public:
		ECLIPSE_ENGINE DirectionalLight();
		ECLIPSE_ENGINE ~DirectionalLight();

	private:
		Math::Vec3 GetDirection();
	};
}