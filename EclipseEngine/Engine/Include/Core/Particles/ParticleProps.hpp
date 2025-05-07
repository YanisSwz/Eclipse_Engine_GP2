#pragma once
#include "Maths.hpp"

namespace Core
{
	struct ParticleProps
	{
		float lifeTime = 1.f;
		
		Math::Vec3 positionOffset{ 0.f, 0.f, 0.f };
		Math::Vec3 positionVariation{ 0.f, 0.f, 0.f };

		float sizeBegin = 1.f;
		float sizeEnd = 1.f;
		float sizeVariation = 0.f;

		Math::Vec4 colorBegin{ 1.f, 1.f, 1.f, 1.f };
		Math::Vec4 colorEnd{ 1.f, 1.f, 1.f, 1.f };

		Math::Vec3 velocity{ 0.f, 0.f, 0.f };
		Math::Vec3 velocityVariation{ 0.f, 0.f, 0.f };
	};
}