#include "Core/Particles/ParticleEmitter.hpp"
#include "Core/GameObject.hpp"
#include "Logger.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Mesh.hpp"

namespace Core
{
	ParticleEmitter::ParticleEmitter()
	{
		particleProps.mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(particleProps.defaultMeshName);
	}

	ParticleEmitter::ParticleEmitter(ParticleEmitterProps _particleEmitterProps, ParticleProps _particleProps)
	{
		particleEmitterProps = _particleEmitterProps;
		particleProps = _particleProps;
		particleProps.mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(particleProps.defaultMeshName);
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
		// Return if particle doesn't have mesh
		if (!particleProps.mesh)
		{
			particleProps.mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(particleProps.defaultMeshName);
			if (!particleProps.mesh)
				return;
		}

		// If Simulation is playing, try to spawn another particles
		if (m_simulationState == SIMULATION_STATE::PLAY)
		{
			if (m_simulationTimeRemaining > 0.f || particleEmitterProps.bIsLooping)
			{
				// Check if simulation is not looping
				// If it's not looping update simulation time remaining 
				// Stop the simulation and return if simulation time remaining is under 0
				if (!particleEmitterProps.bIsLooping)
				{
					m_simulationTimeRemaining -= _deltaTime;
					if (m_simulationTimeRemaining <= 0.f)
					{
						m_simulationState = SIMULATION_STATE::STOP;
						return;
					}
				}

				// Update spawn rate remaining
				if (m_spawnRateRemaining > 0.f)
				{
					m_spawnRateRemaining -= _deltaTime;
				}
				else
				{
					// Try to spawn new particles while spawn rate remaining is under 0
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

		// Update all particles data
		UpdateParticles(_deltaTime);
	}

	ParticleEmitterRenderData ParticleEmitter::GetRenderData()
	{
		ParticleEmitterRenderData particleEmitterRenderData;
		if (!particleProps.mesh)
			particleEmitterRenderData.particleMesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(particleProps.defaultMeshName);
		particleEmitterRenderData.particleMesh = particleProps.mesh;
		particleEmitterRenderData.particleTexture = particleProps.texture;
		particleEmitterRenderData.bIsBillboard = particleProps.bIsBillboard;

		ParticleRenderData particleRenderData;
		for (int i = static_cast<int>(m_particles.size()) - 1; i >= 0; --i)
		{
			if (m_particles[i].isEnable)
			{
				particleRenderData.color = m_particles[i].color / 255.f;
				particleRenderData.position = m_particles[i].position;
				particleRenderData.size = m_particles[i].size;
				particleEmitterRenderData.particlesRenderData.push_back(particleRenderData);
			}
		}
		return particleEmitterRenderData;
	}

	void ParticleEmitter::Serialize(json& _j)
	{
		Math::Vec3 positionOffset = particleProps.positionOffset;
		Math::Vec3 positionVariation = particleProps.positionVariation;
		Math::Vec4 colorBegin = particleProps.colorBegin / 255.f;
		Math::Vec4 colorEnd = particleProps.colorEnd / 255.f;
		Math::Vec3 velocityBegin = particleProps.velocityBegin;
		Math::Vec3 velocityEnd = particleProps.velocityEnd;
		Math::Vec3 velocityVariationBegin = particleProps.velocityVariationBegin;
		Math::Vec3 velocityVariationEnd = particleProps.velocityVariationEnd;
		std::string meshName = particleProps.defaultMeshName;
		if (particleProps.mesh)
			meshName = particleProps.mesh->name;
		std::string textureName = "None";
		if (particleProps.texture)
			textureName = particleProps.texture->name;

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
				{"MeshName", meshName},
				{"TextureName", textureName},
				{"IsBillboard", particleProps.bIsBillboard},
				{"LifeTime", particleProps.lifeTime},
				{"LifeTimeVariation", particleProps.lifeTimeVariation},
				{"PositionOffset", { positionOffset.x, positionOffset.y, positionOffset.z }},
				{"PositionVariation", { positionVariation.x, positionVariation.y, positionVariation.z }},
				{"BeginSize", particleProps.sizeBegin},
				{"EndSize", particleProps.sizeEnd},
				{"SizeVariation", particleProps.sizeEnd},
				{"BeginColor", { colorBegin.x, colorBegin.y, colorBegin.z, colorBegin.w }}, // RGBA
				{"EndColor", { colorEnd.x, colorEnd.y, colorEnd.z, colorEnd.w }}, // RGBA
				{"BeginVelocity", { velocityBegin.x, velocityBegin.y, velocityBegin.z }},
				{"EndVelocity", { velocityEnd.x, velocityEnd.y, velocityEnd.z }},
				{"VelocityVariationBegin", { velocityVariationBegin.x, velocityVariationBegin.y, velocityVariationBegin.z }},
				{"VelocityVariationEnd", { velocityVariationEnd.x, velocityVariationEnd.y, velocityVariationEnd.z }}
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
		float velocityBegin[3];
		float velocityEnd[3];
		float velocityVariationBegin[3];
		float velocityVariationEnd[3];

		json particleEmitterPropsJson = _j["ParticleEmitterProps"];
		json particlePropsJson = _j["ParticleProps"];

		_j.at("IsActive").get_to(bIsActive);

		// Deserialize Particle Emitter Props
		particleEmitterPropsJson.at("MaxParticleNumber").get_to(particleEmitterProps.maxNbParticles);
		particleEmitterPropsJson.at("SpawnRate").get_to(particleEmitterProps.particleSpawnRate);
		particleEmitterPropsJson.at("SpawnRateVariation").get_to(particleEmitterProps.particleSpawnRateVariation);
		particleEmitterPropsJson.at("SimulationDuration").get_to(particleEmitterProps.simulationDuration);
		particleEmitterPropsJson.at("IsLooping").get_to(particleEmitterProps.bIsLooping);

		// Deserialize Particle Props
		std::string meshName;
		particlePropsJson.at("MeshName").get_to(meshName);
		particleProps.mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(meshName);
		
		std::string textureName;
		particlePropsJson.at("TextureName").get_to(textureName);
		if (textureName != "None")
			particleProps.texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(textureName);
		else
			particleProps.texture = nullptr;
		
		particlePropsJson.at("IsBillboard").get_to(particleProps.bIsBillboard);
		particlePropsJson.at("PositionOffset").get_to(positionOffset);
		particlePropsJson.at("PositionVariation").get_to(positionVariation);
		particlePropsJson.at("BeginColor").get_to(colorBegin);
		particlePropsJson.at("EndColor").get_to(colorEnd);
		particlePropsJson.at("BeginVelocity").get_to(velocityBegin);
		particlePropsJson.at("EndVelocity").get_to(velocityEnd);
		particlePropsJson.at("VelocityVariationBegin").get_to(velocityVariationBegin);
		particlePropsJson.at("VelocityVariationEnd").get_to(velocityVariationEnd);
		particlePropsJson.at("LifeTime").get_to(particleProps.lifeTime);
		particlePropsJson.at("LifeTimeVariation").get_to(particleProps.lifeTimeVariation);
		particlePropsJson.at("BeginSize").get_to(particleProps.sizeBegin);
		particlePropsJson.at("EndSize").get_to(particleProps.sizeEnd);
		particlePropsJson.at("SizeVariation").get_to(particleProps.sizeVariation);

		SetActive(bIsActive);
		particleProps.positionOffset = { positionOffset[0], positionOffset[1], positionOffset[2] };
		particleProps.positionVariation = { positionVariation[0], positionVariation[1], positionVariation[2] };
		particleProps.colorBegin = { colorBegin[0], colorBegin[1], colorBegin[2], colorBegin[3] };
		particleProps.colorEnd = { colorEnd[0], colorEnd[1], colorEnd[2], colorEnd[3] };
		particleProps.velocityBegin = { velocityBegin[0], velocityBegin[1], velocityBegin[2] };
		particleProps.velocityEnd = { velocityEnd[0], velocityEnd[1], velocityEnd[2] };
		particleProps.velocityVariationBegin = { velocityVariationBegin[0], velocityVariationBegin[1], velocityVariationBegin[2] };
		particleProps.velocityVariationEnd = { velocityVariationEnd[0], velocityVariationEnd[1], velocityVariationEnd[2] };
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

		// LifeTime
		spawnedParticle->lifeTimeRemaining = particleProps.lifeTime + particleProps.lifeTimeVariation * Math::Tools::Random();
		
		// Color
		spawnedParticle->color = particleProps.colorBegin;
		
		// Size
		spawnedParticle->size = particleProps.sizeBegin + (particleProps.sizeVariation * Math::Tools::Random() - (particleProps.sizeVariation / 2.f));
		
		// Position
		Math::Vec3 randomPos{		particleProps.positionVariation.x * Math::Tools::Random() - (particleProps.positionVariation.x / 2.f),
									particleProps.positionVariation.y * Math::Tools::Random() - (particleProps.positionVariation.y / 2.f),
									particleProps.positionVariation.z * Math::Tools::Random() - (particleProps.positionVariation.z / 2.f) };
		spawnedParticle->position = m_gameObject->transform->GetPosition() + particleProps.positionOffset + randomPos;
		
		// Velocity
		Math::Vec3 randomVelocityBegin{ particleProps.velocityVariationBegin.x * Math::Tools::Random() - (particleProps.velocityVariationBegin.x / 2.f),
									particleProps.velocityVariationBegin.y * Math::Tools::Random() - (particleProps.velocityVariationBegin.y / 2.f),
									particleProps.velocityVariationBegin.z * Math::Tools::Random() - (particleProps.velocityVariationBegin.z / 2.f) };

		Math::Vec3 randomVelocityEnd{ particleProps.velocityVariationEnd.x * Math::Tools::Random() - (particleProps.velocityVariationEnd.x / 2.f),
									particleProps.velocityVariationEnd.y * Math::Tools::Random() - (particleProps.velocityVariationEnd.y / 2.f),
									particleProps.velocityVariationEnd.z * Math::Tools::Random() - (particleProps.velocityVariationEnd.z / 2.f) };
		spawnedParticle->velocityBegin = particleProps.velocityBegin + randomVelocityBegin;
		spawnedParticle->velocityEnd = particleProps.velocityEnd + randomVelocityEnd;
		spawnedParticle->velocity = spawnedParticle->velocityBegin;
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

			// Update LifeTime
			m_particles[i].lifeTimeRemaining -= _deltaTime;
			if (m_particles[i].lifeTimeRemaining <= 0.f)
			{
				m_particles[i].isEnable = false;
				--m_particlesCount;
				continue;
			}
			else if (m_particles[i].lifeTimeRemaining > particleProps.lifeTime + particleProps.lifeTimeVariation)
			{
				m_particles[i].lifeTimeRemaining = particleProps.lifeTime;
			}

			float ltr = m_particles[i].lifeTimeRemaining / particleProps.lifeTime;
			m_particles[i].color = particleProps.colorBegin * ltr + particleProps.colorEnd * (1 - ltr);
			m_particles[i].size = particleProps.sizeBegin * ltr + particleProps.sizeEnd * (1 - ltr);
			m_particles[i].velocity = m_particles[i].velocityBegin * ltr + m_particles[i].velocityEnd * (1 - ltr);
			m_particles[i].position += (m_particles[i].velocity * _deltaTime);
		}
	}
}