#include "Audio/AudioSystem.hpp"
#include "Logger.hpp"

namespace Core
{
	void AudioSystem::Init()
	{
		m_audioEngine.init();
		m_audioEngine.setVisualizationEnable(true);

		/*m_startupSound.load("Assets/Audio/startup.mp3");
		m_startupSound.setVolume(2.f);*/
	}

	void AudioSystem::Destroy()
	{
		m_audioEngine.deinit();
	}

	void AudioSystem::PlayStartUp()
	{
		//m_audioEngine.play(m_startupSound);
	}

	AudioSource* AudioSystem::Add()
	{
		if (m_currentCount >= MAX_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentCount; ++i)
		{
			if (m_audioEmitters[i].IsDestroyed())
			{
				m_audioEmitters[i].Remove();
				m_audioEmitters[i].~AudioSource();
				new (&m_audioEmitters[i]) AudioSource(&m_audioEngine);
				return &m_audioEmitters[i];
			}
		}

		m_audioEmitters[m_currentCount].~AudioSource();
		new (&m_audioEmitters[m_currentCount]) AudioSource(&m_audioEngine);
		
		++m_currentCount;
		return &m_audioEmitters[m_currentCount - 1];
	}
}