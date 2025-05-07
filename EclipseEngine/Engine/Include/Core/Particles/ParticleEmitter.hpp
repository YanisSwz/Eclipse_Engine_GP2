#pragma once
#include "Core/Component.hpp"
#include "Core/Particles/ParticleEmitterProps.hpp"
#include "Core/Particles/ParticleProps.hpp"
#include "Core/Particles/Particle.hpp"
#include "Core/Particles/ParticleRenderData.hpp"
#include "ProjectExports.hpp"
#include <vector>

namespace Core
{
	class ParticleEmitter : public Component
	{
	public:
		ParticleEmitter() = default;
		ParticleEmitter(ParticleEmitterProps _particleEmitterProps, ParticleProps _particleProps);
		~ParticleEmitter() = default;

		ECLIPSE_ENGINE Particle* AddParticle();
		ECLIPSE_ENGINE void SetParticleEmitterProps(ParticleEmitterProps _particleEmitterProps);
		ECLIPSE_ENGINE void SetParticleProps(ParticleProps _particleProps);

		ECLIPSE_ENGINE void Update(float _deltaTime);
		ECLIPSE_ENGINE std::vector<ParticleRenderData> GetRenderData();

	private:
		ParticleEmitterProps m_particleEmitterProps;
		ParticleProps m_particleProps;

		static const int MAX_PARTICLE_COUNT = 2000;
		int m_particlesCount;
		std::vector<Particle> m_particles;

		float m_spawnRateRemaining = 0.f;

		void SpawnParticle();
		void UpdateParticle(float _deltaTime);
	};
}