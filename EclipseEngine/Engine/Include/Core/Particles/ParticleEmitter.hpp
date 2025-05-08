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
		ECLIPSE_ENGINE ParticleEmitter();
		ECLIPSE_ENGINE ParticleEmitter(ParticleEmitterProps _particleEmitterProps, ParticleProps _particleProps);
		ECLIPSE_ENGINE ~ParticleEmitter() = default;

		static const int MAX_PARTICLE_COUNT = 2000;
		ParticleEmitterProps particleEmitterProps;
		ParticleProps particleProps;

		ECLIPSE_ENGINE void SetActive(bool _activate) override;
		ECLIPSE_ENGINE Particle* AddParticle();
		ECLIPSE_ENGINE void Play();
		ECLIPSE_ENGINE bool IsPlaying() const;
		ECLIPSE_ENGINE void Stop();

		ECLIPSE_ENGINE void Update(float _deltaTime);
		ECLIPSE_ENGINE std::vector<ParticleRenderData> GetRenderData();
		
		ECLIPSE_ENGINE void Destroy() override;
		ECLIPSE_ENGINE void Delete();

		ECLIPSE_ENGINE void Serialize(json& _j) override;
		ECLIPSE_ENGINE void Deserialize(const json& _j) override;

	private:
		enum class SIMULATION_STATE
		{
			PLAY,
			STOP
		};

		SIMULATION_STATE m_simulationState = SIMULATION_STATE::PLAY;
		int m_particlesCount = 0;
		std::vector<Particle> m_particles;

		float m_simulationTimeRemaining = 0.f;
		float m_spawnRateRemaining = 0.f;

		void SpawnParticle();
		void ResetParticles();
		void UpdateParticles(float _deltaTime);
	};
}