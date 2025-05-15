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
		std::string defaultTextureName = "WhitTexture.img";
		Resource::Texture* texture = nullptr;
		bool bIsBillboard = true;

		float lifeTime = 1.f;
		
		Math::Vec3 positionOffset{ 0.f, 0.f, 0.f };
		Math::Vec3 positionVariation{ 0.f, 0.f, 0.f };

		float sizeBegin = 75.f;
		float sizeEnd = 25.f;
		float sizeVariation = 0.f;

		Math::Vec4 colorBegin{ 255.f, 0.f, 255.f, 255.f };
		Math::Vec4 colorEnd{ 255.f, 0.f, 255.f, 255.f };

		Math::Vec3 velocity{ 0.f, 0.f, 0.f };
		Math::Vec3 velocityVariation{ 1.f, 1.f, 1.f };
	};
}