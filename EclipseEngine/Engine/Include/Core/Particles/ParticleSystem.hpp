#pragma once
#include "Core/Particles/ParticleEmitter.hpp"
#include "Core/Particles/ParticleRenderData.hpp"
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
		ECLIPSE_ENGINE std::vector<ParticleEmitterRenderData> GetRenderData();

		ECLIPSE_ENGINE void Reset();

	private:
		static const int MAX_PARTICLE_EMITTER_COUNT = 50;
		int m_particleEmitterCount = 0;
		ParticleEmitter m_particleEmitter[MAX_PARTICLE_EMITTER_COUNT];
	};
}