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
			if (m_simulationTimeRemaining > 0.f || particleEmitterProps.bIsLooping)
			{
				if (!particleEmitterProps.bIsLooping)
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

	void ParticleEmitter::Serialize(json& _j)
	{
		Math::Vec3 positionOffset = particleProps.positionOffset;
		Math::Vec3 positionVariation = particleProps.positionVariation;
		Math::Vec4 colorBegin = particleProps.colorBegin / 255.f;
		Math::Vec4 colorEnd = particleProps.colorEnd / 255.f;
		Math::Vec3 velocity = particleProps.velocity;
		Math::Vec3 velocityVariation = particleProps.velocityVariation;

		_j["ParticleEmitter"] = json{
			{"IsActive", IsActive()},
			json{"ParticleEmitterProps", { 
				{"MaxParticleNumber", particleEmitterProps.maxNbParticles},
				{"SpawnRate", particleEmitterProps.particleSpawnRate},
				{"SpawnRateVariation", particleEmitterProps.particleSpawnRateVariation},
				{"SimulationDuration", particleEmitterProps.simulationDuration},
				{"IsLooping", particleEmitterProps.bIsLooping}
			}},
			json{"ParticleProps", { 
				{"LifeTime", particleProps.lifeTime},
				{"PositionOffset", { positionOffset.x, positionOffset.y, positionOffset.z }},
				{"PositionVariation", { positionVariation.x, positionVariation.y, positionVariation.z }},
				{"BeginSize", particleProps.sizeBegin},
				{"EndSize", particleProps.sizeEnd},
				{"SizeVariation", particleProps.sizeEnd},
				{"BeginColor", { colorBegin.x, colorBegin.y, colorBegin.z, colorBegin.w }}, // RGBA
				{"EndColor", { colorEnd.x, colorEnd.y, colorEnd.z, colorEnd.w }}, // RGBA
				{"Velocity", { velocity.x, velocity.y, velocity.z }},
				{"VelocityVariation", { velocityVariation.x, velocityVariation.y, velocityVariation.z }}
			}},
		};
	}

	void ParticleEmitter::Deserialize(const json& _j)
	{
		bool bIsActive;
		float positionOffset[3];
		float positionVariation[3];
		float colorBegin[4];
		float colorEnd[4];
		float velocity[3];
		float velocityVariation[3];

		json particleEmitterPropsJson = _j["ParticleEmitterProps"];
		json particlePropsJson = _j["ParticleProps"];

		_j.at("IsActive").get_to(bIsActive);

		particlePropsJson.at("PositionOffset").get_to(positionOffset);
		particlePropsJson.at("PositionVariation").get_to(positionVariation);
		particlePropsJson.at("BeginColor").get_to(colorBegin);
		particlePropsJson.at("EndColor").get_to(colorEnd);
		particlePropsJson.at("Velocity").get_to(velocity);
		particlePropsJson.at("VelocityVariation").get_to(velocityVariation);

		particleEmitterPropsJson.at("MaxParticleNumber").get_to(particleEmitterProps.maxNbParticles);
		particleEmitterPropsJson.at("SpawnRate").get_to(particleEmitterProps.particleSpawnRate);
		particleEmitterPropsJson.at("SpawnRateVariation").get_to(particleEmitterProps.particleSpawnRateVariation);
		particleEmitterPropsJson.at("SimulationDuration").get_to(particleEmitterProps.simulationDuration);
		particleEmitterPropsJson.at("IsLooping").get_to(particleEmitterProps.bIsLooping);
		
		particlePropsJson.at("LifeTime").get_to(particleProps.lifeTime);
		particlePropsJson.at("BeginSize").get_to(particleProps.sizeBegin);
		particlePropsJson.at("EndSize").get_to(particleProps.sizeEnd);
		particlePropsJson.at("SizeVariation").get_to(particleProps.sizeVariation);

		SetActive(bIsActive);
		particleProps.positionOffset = { positionOffset[0], positionOffset[1], positionOffset[2] };
		particleProps.positionVariation = { positionVariation[0], positionVariation[1], positionVariation[2] };
		particleProps.colorBegin = { colorBegin[0] * 255.f, colorBegin[1] * 255.f, colorBegin[2] * 255.f, colorBegin[3] * 255.f };
		particleProps.colorEnd = { colorEnd[0] * 255.f, colorEnd[1] * 255.f, colorEnd[2] * 255.f, colorEnd[3] * 255.f };
		particleProps.velocity = { velocity[0], velocity[1], velocity[2] };
		particleProps.velocityVariation = { velocityVariation[0], velocityVariation[1], velocityVariation[2] };
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