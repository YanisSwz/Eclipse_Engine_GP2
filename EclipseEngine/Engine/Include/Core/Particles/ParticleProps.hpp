#pragma once
#include "Maths.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/Texture.hpp"
#include <string>

namespace Core
{
	struct ParticleProps
	{
		std::string defaultMeshName = "Quad.obj";
		Resource::Mesh* mesh = nullptr;
		Resource::Texture* texture = nullptr;
		bool bIsBillboard = true;

		float lifeTime = 1.f;
		float lifeTimeVariation = 0.f;
		
		Math::Vec3 positionOffset{ 0.f, 0.f, 0.f };
		Math::Vec3 positionVariation{ 0.f, 0.f, 0.f };

		float sizeBegin = 75.f;
		float sizeEnd = 25.f;
		float sizeVariation = 0.f;

		Math::Vec4 colorBegin{ 255.f, 0.f, 255.f, 255.f };
		Math::Vec4 colorEnd{ 255.f, 0.f, 255.f, 255.f };

		Math::Vec3 velocityBegin{ 0.f, 0.f, 0.f };
		Math::Vec3 velocityEnd{ 0.f, 0.f, 0.f };
		Math::Vec3 velocityVariationBegin{ 1.f, 1.f, 1.f };
		Math::Vec3 velocityVariationEnd{ 1.f, 1.f, 1.f };

		//Math::Vec3 rotationBegin{ 0.f, 0.f, 0.f };
		//Math::Vec3 rotationEnd{ 0.f, 0.f, 0.f };
	};
}