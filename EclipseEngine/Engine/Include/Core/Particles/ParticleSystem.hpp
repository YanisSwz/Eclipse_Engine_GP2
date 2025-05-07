#pragma once
#include "Core/Particles/ParticleEmitter.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class ParticleSystem
	{
	public:
		ParticleSystem();
		~ParticleSystem();
		ECLIPSE_ENGINE ParticleEmitter* AddParticleEmitter();

		ECLIPSE_ENGINE void Update(float _deltaTime);
		ECLIPSE_ENGINE std::vector<std::vector<ParticleRenderData>> GetRenderData();

	private:
		static const int MAX_PARTICLE_EMITTER_COUNT = 100;
		int m_particleEmitterCount = 0;
		ParticleEmitter m_particleEmitter[MAX_PARTICLE_EMITTER_COUNT];
	};
}