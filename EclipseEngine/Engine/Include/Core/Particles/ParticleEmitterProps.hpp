#pragma once

namespace Core
{
	struct ParticleEmitterProps
	{
		unsigned int maxNbParticles = 100;
		float particleSpawnRateVariation = 1.f;
		float particleSpawnRate = 1.f;
	};
}