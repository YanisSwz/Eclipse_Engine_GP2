#include "Core/Particles/ParticleEmitter.hpp"
#include "Core/GameObject.hpp"
#include "Logger.hpp"

namespace Core
{
	ParticleEmitter::ParticleEmitter(ParticleEmitterProps _particleEmitterProps, ParticleProps _particleProps)
	{
		m_particleEmitterProps = _particleEmitterProps;
		m_particleProps = _particleProps;
		m_particles.resize(_particleEmitterProps.maxNbParticles);
	}

	Particle* ParticleEmitter::AddParticle()
	{
		if (static_cast<unsigned int>(m_particlesCount) >= m_particleEmitterProps.maxNbParticles)
		{
			return nullptr;
		}

		for (int i = 0; i < m_particlesCount; ++i)
		{
			if (!m_particles[i].isEnable)
			{
				m_particles[i].isEnable = true;
				return &m_particles[i];
			}
		}

		m_particles[m_particlesCount].isEnable = true;
		++m_particlesCount;
		return &m_particles[m_particlesCount - 1];
	}

	void ParticleEmitter::SetParticleEmitterProps(ParticleEmitterProps _particleEmitterProps)
	{
		m_particleEmitterProps = _particleEmitterProps;
		if (_particleEmitterProps.maxNbParticles < MAX_PARTICLE_COUNT)
			m_particles.resize(_particleEmitterProps.maxNbParticles);
		else
			m_particles.resize(MAX_PARTICLE_COUNT);
	}

	void ParticleEmitter::SetParticleProps(ParticleProps _particleProps)
	{
		m_particleProps = _particleProps;
	}

	void ParticleEmitter::Update(float _deltaTime)
	{
		if (m_spawnRateRemaining > 0.f)
		{
			m_spawnRateRemaining -= _deltaTime;
		}
		else
		{
			if (static_cast<unsigned int>(m_particlesCount) < m_particleEmitterProps.maxNbParticles)
			{
				while (m_spawnRateRemaining <= 0.f)
				{
					m_spawnRateRemaining += m_particleEmitterProps.particleSpawnRate + Math::Tools::Random() * m_particleEmitterProps.particleSpawnRateVariation;
					SpawnParticle();
				}
			}
		}

		for (int i = 0; i < m_particlesCount; ++i)
		{
			if (!m_particles[i].isEnable)
				continue;

			m_particles[i].lifeTimeRemaining -= _deltaTime;
			if (m_particles[i].lifeTimeRemaining <= 0.f)
			{
				m_particles[i].isEnable = false;
				--m_particlesCount;
			}

			float ltr = m_particles[i].lifeTimeRemaining / m_particleProps.lifeTime;
			m_particles[i].color = m_particleProps.colorBegin * ltr + m_particleProps.colorEnd * (1 - ltr);
			m_particles[i].size = m_particleProps.sizeBegin * ltr + m_particleProps.sizeEnd * (1 - ltr);
			m_particles[i].position += (m_particles[i].velocity * _deltaTime);
		}
	}

	void ParticleEmitter::SpawnParticle()
	{
		Particle* spawnedParticle = AddParticle();
		if (!spawnedParticle)
			return;

		spawnedParticle->color = m_particleProps.colorBegin;
		spawnedParticle->lifeTimeRemaining = m_particleProps.lifeTime;
		Math::Vec3 randomPos{ m_particleProps.positionVariation.x * Math::Tools::Random() - (m_particleProps.positionVariation.x / 2.f),
								m_particleProps.positionVariation.y * Math::Tools::Random() - (m_particleProps.positionVariation.y / 2.f),
								m_particleProps.positionVariation.z * Math::Tools::Random() - (m_particleProps.positionVariation.z / 2.f) };
		spawnedParticle->position = m_gameObject->transform->GetPosition() + m_particleProps.positionOffset + randomPos;
		spawnedParticle->size = m_particleProps.sizeBegin + (m_particleProps.sizeVariation * Math::Tools::Random() - (m_particleProps.sizeVariation / 2.f));
		spawnedParticle->velocity = m_particleProps.velocity + (m_particleProps.velocityVariation * Math::Tools::Random() - (m_particleProps.velocityVariation / 2.f));
	}

	void ParticleEmitter::UpdateParticle(float _deltaTime)
	{
	}

	std::vector<ParticleRenderData> ParticleEmitter::GetRenderData()
	{
		std::vector<ParticleRenderData> renderData;
		ParticleRenderData particleRenderData;
		for (int i = m_particlesCount - 1; i >= 0; --i)
		{
			if (m_particles[i].isEnable)
			{
				particleRenderData.color = m_particles[i].color;
				particleRenderData.position = m_particles[i].position;
				particleRenderData.size = m_particles[i].size;
				renderData.push_back(particleRenderData);
			}
		}
		return renderData;
	}
}