#include "Audio/AudioSystem.hpp"
#include "Logger.hpp"

namespace Core
{
	void AudioSystem::Init()
	{
		m_audioEngine.init();

		m_startupSound.load("Assets/Audio/startup.mp3");
		m_startupSound.setVolume(2.f);
	}

	void AudioSystem::Destroy()
	{
		m_audioEngine.deinit();
	}

	void AudioSystem::PlayStartUp()
	{
		m_audioEngine.play(m_startupSound);
	}

	AudioEmitter* AudioSystem::Add()
	{
		if (m_currentCount >= MAX_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentCount; ++i)
		{
			if (m_audioEmitters[i].IsDestroyed())
			{
				m_audioEmitters[i].Remove();
				m_audioEmitters[i].~AudioEmitter();
				new (&m_audioEmitters[i]) AudioEmitter(&m_audioEngine);
				return &m_audioEmitters[i];
			}
		}

		m_audioEmitters[m_currentCount].~AudioEmitter();
		new (&m_audioEmitters[m_currentCount]) AudioEmitter(&m_audioEngine);
		
		++m_currentCount;
		return &m_audioEmitters[m_currentCount - 1];
	}
}