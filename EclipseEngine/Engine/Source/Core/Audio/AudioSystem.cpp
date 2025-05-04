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
		if (m_currentListener != nullptr)
			m_currentListener->Update();
		m_audioEngine.update3dAudio();
	}

	void AudioSystem::SetPause(bool _pause)
	{
		m_audioEngine.setPauseAll(_pause);
	}

	void AudioSystem::Stop()
	{
		m_audioEngine.stopAll();
	}

	void AudioSystem::PlayStartUp()
	{
		//m_audioEngine.play(m_startupSound);
	}

	AudioSource* AudioSystem::AddAudioSource()
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

	AudioListener* AudioSystem::AddAudioListener()
	{
		if (m_currentListenersCount >= MAX_LISTENER_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentListenersCount; ++i)
		{
			if (m_audioListeners[i].IsDestroyed())
			{
				m_audioListeners[i].Remove();
				m_audioListeners[i].~AudioListener();
				new (&m_audioListeners[i]) AudioListener(&m_audioEngine);
				m_audioListeners[i].SetActive(true);
				if (m_currentListener == nullptr)
					m_currentListener = &m_audioListeners[i];
				return &m_audioListeners[i];
			}
		}

		m_audioListeners[m_currentListenersCount].~AudioListener();
		new (&m_audioListeners[m_currentListenersCount]) AudioListener(&m_audioEngine);
		m_audioListeners[m_currentListenersCount].SetActive(true);
		if (m_currentListener == nullptr)
			m_currentListener = &m_audioListeners[m_currentListenersCount];
		++m_currentListenersCount;
		return &m_audioListeners[m_currentListenersCount - 1];
	}
}