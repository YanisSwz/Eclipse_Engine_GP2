#pragma once
#include "Maths.hpp"
#include <vector>

namespace Resource
{
	class Mesh;
	class Texture;
}

namespace Core
{
	struct ParticleRenderData
	{
		Math::Vec4 color;
		Math::Vec3 position;
		float size;
	};

	struct ParticleEmitterRenderData 
	{
		Resource::Mesh* particleMesh;
		Resource::Texture* particleTexture;
		bool bIsBillboard;
		std::vector<ParticleRenderData> particlesRenderData;
	};
}