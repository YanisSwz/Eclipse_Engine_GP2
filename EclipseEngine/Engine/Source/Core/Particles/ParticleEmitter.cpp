#include "Core/Particles/ParticleEmitter.hpp"
#include "Core/GameObject.hpp"
#include "Logger.hpp"

namespace Core
{
	ParticleEmitter::ParticleEmitter()
	{
	}

	ParticleEmitter::ParticleEmitter(ParticleEmitterProps _particleEmitterProps, ParticleProps _particleProps)
	{
		particleEmitterProps = _particleEmitterProps;
		particleProps = _particleProps;
	}

	void ParticleEmitter::SetActive(bool _activate)
	{
		m_active = _activate;
		if (!m_active)
		{
			Stop();
			ResetParticles();
		}
	}

	Particle* ParticleEmitter::AddParticle()
	{
		if (m_particlesCount >= particleEmitterProps.maxNbParticles)
		{
			return nullptr;
		}

		for (int i = 0; i < m_particles.size(); ++i)
		{
			if (!m_particles[i].isEnable)
			{
				m_particles[i].isEnable = true;
				++m_particlesCount;
				return &m_particles[i];
			}
		}

		m_particles.push_back(Particle{});
		m_particles[m_particlesCount].isEnable = true;
		++m_particlesCount;
		return &m_particles[m_particlesCount - 1];
	}

	void ParticleEmitter::Play()
	{
		m_simulationTimeRemaining = particleEmitterProps.simulationDuration;
		m_spawnRateRemaining = 0.f;
		m_simulationState = SIMULATION_STATE::PLAY;
	}

	bool ParticleEmitter::IsPlaying() const
	{
		return m_simulationState == SIMULATION_STATE::PLAY;
	}

	void ParticleEmitter::Stop()
	{
		m_simulationState = SIMULATION_STATE::STOP;
	}

	void ParticleEmitter::Update(float _deltaTime)
	{
		if (m_simulationState == SIMULATION_STATE::PLAY)
		{
			if (m_simulationTimeRemaining > 0.f || particleEmitterProps.bIsLoop)
			{
				if (!particleEmitterProps.bIsLoop)
				{
					m_simulationTimeRemaining -= _deltaTime;
					if (m_simulationTimeRemaining <= 0.f)
					{
						m_simulationState = SIMULATION_STATE::STOP;
						return;
					}
				}

				if (m_spawnRateRemaining > 0.f)
				{
					m_spawnRateRemaining -= _deltaTime;
				}
				else
				{
					while (m_spawnRateRemaining <= 0.f)
					{
						if (particleEmitterProps.particleSpawnRate == 0.f)
							break;

						if (m_particlesCount <= particleEmitterProps.maxNbParticles)
							SpawnParticle();

						m_spawnRateRemaining += particleEmitterProps.particleSpawnRate + Math::Tools::Random() * particleEmitterProps.particleSpawnRateVariation;
					}
				}
			}
		}

		UpdateParticles(_deltaTime);
	}

	std::vector<ParticleRenderData> ParticleEmitter::GetRenderData()
	{
		std::vector<ParticleRenderData> renderData;
		ParticleRenderData particleRenderData;
		for (int i = static_cast<int>(m_particles.size()) - 1; i >= 0; --i)
		{
			if (m_particles[i].isEnable)
			{
				particleRenderData.color = m_particles[i].color / 255.f;
				particleRenderData.position = m_particles[i].position;
				particleRenderData.size = m_particles[i].size;
				renderData.push_back(particleRenderData);
			}
		}
		return renderData;
	}

	void ParticleEmitter::Destroy()
	{
		m_active = false;
		m_destroyed = true;
		Delete();
	}

	void ParticleEmitter::Delete()
	{
		ResetParticles();
	}

	void ParticleEmitter::SpawnParticle()
	{
		Particle* spawnedParticle = AddParticle();
		if (!spawnedParticle)
			return;

		spawnedParticle->color = particleProps.colorBegin;
		spawnedParticle->lifeTimeRemaining = particleProps.lifeTime;
		Math::Vec3 randomPos{ particleProps.positionVariation.x * Math::Tools::Random() - (particleProps.positionVariation.x / 2.f),
								particleProps.positionVariation.y * Math::Tools::Random() - (particleProps.positionVariation.y / 2.f),
								particleProps.positionVariation.z * Math::Tools::Random() - (particleProps.positionVariation.z / 2.f) };
		spawnedParticle->position = m_gameObject->transform->GetPosition() + particleProps.positionOffset + randomPos;
		spawnedParticle->size = particleProps.sizeBegin + (particleProps.sizeVariation * Math::Tools::Random() - (particleProps.sizeVariation / 2.f));
		Math::Vec3 randomVelocity{ particleProps.velocityVariation.x * Math::Tools::Random() - (particleProps.velocityVariation.x / 2.f),
								particleProps.velocityVariation.y * Math::Tools::Random() - (particleProps.velocityVariation.y / 2.f),
								particleProps.velocityVariation.z * Math::Tools::Random() - (particleProps.velocityVariation.z / 2.f) };
		spawnedParticle->velocity = particleProps.velocity + randomVelocity;
	}

	void ParticleEmitter::ResetParticles()
	{
		m_particles.clear();
		m_particlesCount = 0;
	}

	void ParticleEmitter::UpdateParticles(float _deltaTime)
	{
		for (int i = 0; i < m_particles.size(); ++i)
		{
			if (!m_particles[i].isEnable)
				continue;

			m_particles[i].lifeTimeRemaining -= _deltaTime;
			if (m_particles[i].lifeTimeRemaining <= 0.f)
			{
				m_particles[i].isEnable = false;
				--m_particlesCount;
				continue;
			}
			else if (m_particles[i].lifeTimeRemaining > particleProps.lifeTime)
			{
				m_particles[i].lifeTimeRemaining = particleProps.lifeTime;
			}

			float ltr = m_particles[i].lifeTimeRemaining / particleProps.lifeTime;
			m_particles[i].color = particleProps.colorBegin * ltr + particleProps.colorEnd * (1 - ltr);
			m_particles[i].size = particleProps.sizeBegin * ltr + particleProps.sizeEnd * (1 - ltr);
			m_particles[i].position += (m_particles[i].velocity * _deltaTime);
		}
	}
}