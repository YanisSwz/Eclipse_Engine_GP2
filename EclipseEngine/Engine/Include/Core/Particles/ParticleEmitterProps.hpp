#pragma once

namespace Core
{
	struct ParticleEmitterProps
	{
		int maxNbParticles = 500;
		float particleSpawnRate = 0.01f;
		float particleSpawnRateVariation = 0.f;
		float simulationDuration = 5.f;
		bool bIsLooping = false;
	};
}