#pragma once
#include "Maths.hpp"

namespace Core
{
	struct Particle
	{
		Math::Vec4 color{ 1.f, 1.f, 1.f, 1.f };
		Math::Vec3 position{ 0.f, 0.f, 0.f };
		float lifeTimeRemaining = 0.f;
		Math::Vec3 velocityBegin{ 0.f, 0.f, 0.f };
		Math::Vec3 velocityEnd{ 0.f, 0.f, 0.f };
		Math::Vec3 velocity{ 0.f, 0.f, 0.f };
		float size = 1.f;
		bool isEnable = false;
	};
}