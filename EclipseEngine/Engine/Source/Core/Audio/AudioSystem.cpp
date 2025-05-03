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

	void AudioSystem::Update()
	{
		for (int i = 0; i < m_currentCount; ++i)
			m_audioSources[i].Update();
		m_audioEngine.update3dAudio();
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
			if (m_audioSources[i].IsDestroyed())
			{
				m_audioSources[i].Remove();
				m_audioSources[i].~AudioSource();
				new (&m_audioSources[i]) AudioSource(&m_audioEngine);
				m_audioSources[i].SetActive(true);
				return &m_audioSources[i];
			}
		}

		m_audioSources[m_currentCount].~AudioSource();
		new (&m_audioSources[m_currentCount]) AudioSource(&m_audioEngine);
		m_audioSources[m_currentCount].SetActive(true);
		++m_currentCount;
		return &m_audioSources[m_currentCount - 1];
	}
}