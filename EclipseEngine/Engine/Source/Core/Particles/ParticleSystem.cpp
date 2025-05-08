#include "Core/Particles/ParticleSystem.hpp"
#include "Logger.hpp"

namespace Core
{
	ParticleSystem::ParticleSystem()
	{
	}

	ParticleSystem::~ParticleSystem()
	{
	}

	ParticleEmitter* ParticleSystem::AddParticleEmitter()
	{
		if (m_particleEmitterCount >= MAX_PARTICLE_EMITTER_COUNT)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Maximum capacity of particle emitter reached!");
			return nullptr;
		}

		for (int i = 0; i < m_particleEmitterCount; ++i)
		{
			if (m_particleEmitter[i].IsDestroyed())
			{
				m_particleEmitter[i].Remove();
				m_particleEmitter[i].~ParticleEmitter();
				new (&m_particleEmitter[i]) ParticleEmitter();
				m_particleEmitter[i].SetActive(true);
				return &m_particleEmitter[i];
			}
		}

		m_particleEmitter[m_particleEmitterCount].~ParticleEmitter();
		new (&m_particleEmitter[m_particleEmitterCount]) ParticleEmitter();
		m_particleEmitter[m_particleEmitterCount].SetActive(true);

		++m_particleEmitterCount;

		return &m_particleEmitter[m_particleEmitterCount - 1];
	}

	void ParticleSystem::Update(float _deltaTime)
	{
		for (int i = 0; i < m_particleEmitterCount; ++i)
		{
			if (m_particleEmitter[i].IsActive())
				m_particleEmitter[i].Update(_deltaTime);
		}
	}
	
	std::vector<std::vector<ParticleRenderData>> ParticleSystem::GetRenderData()
	{
		std::vector<std::vector<ParticleRenderData>> renderData;
		for (int i = 0; i < m_particleEmitterCount; ++i)
			renderData.push_back(m_particleEmitter[i].GetRenderData());

		return renderData;
	}

	void ParticleSystem::Reset()
	{
		m_particleEmitterCount = 0;
	}
}