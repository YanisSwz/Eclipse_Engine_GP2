#pragma once
#include "Maths.hpp"

namespace Core
{
	struct ParticleProps
	{
		float lifeTime = 2.f;
		
		Math::Vec3 positionOffset{ 0.f, 0.f, 0.f };
		Math::Vec3 positionVariation{ 0.5f, 0.5f, 0.5f };

		float sizeBegin = 75.f;
		float sizeEnd = 25.f;
		float sizeVariation = 0.f;

		Math::Vec4 colorBegin{ 255.f, 0.f, 255.f, 255.f };
		Math::Vec4 colorEnd{ 255.f, 0.f, 255.f, 255.f };

		Math::Vec3 velocity{ 0.f, 0.f, 0.f };
		Math::Vec3 velocityVariation{ 2.f, 2.f, 3.f };
	};
}