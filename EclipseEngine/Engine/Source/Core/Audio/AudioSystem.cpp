#include "Audio/AudioSystem.hpp"
#include "Logger.hpp"
#include "Resource/ResourceManager.hpp"

namespace Core
{
	AudioSystem::~AudioSystem()
	{
		Stop();
		std::vector<SoLoud::handle> handles = AudioSource::GetChannelHandles();
		for (int i = 0; i < static_cast<int>(handles.size()); ++i)
			m_audioEngine.destroyVoiceGroup(handles[i]);
		m_audioEngine.deinit();
	}

	void AudioSystem::Init()
	{
		m_audioEngine.init();
		m_audioEngine.setVisualizationEnable(true);
		EnableAudio();
		AudioSource::AddChannel("Music", m_audioEngine.createVoiceGroup());
		AudioSource::AddChannel("SFX", m_audioEngine.createVoiceGroup());
		Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Audio engine successfully initialized");
	}

	void AudioSystem::Start()
	{
		if (m_paused)
			m_paused = false;
		ResetAudioSourcesPause();
		if (m_currentListener == nullptr)
		{
			DisableAudio();
			return;
		}
		else
		{
			for (int i = 0; i < m_currentSourcesCount; ++i)
			{
				if (m_audioSources[i].IsPlayingOnAwake() && m_audioSources[i].IsActive() && m_audioSources[i].GetClip() != nullptr)
					m_audioSources[i].Play();
			}
		}
	}

	void AudioSystem::Update()
	{
		m_stereoVolume[0] = m_audioEngine.getApproximateVolume(0);
		m_stereoVolume[1] = m_audioEngine.getApproximateVolume(1);
		if (m_currentListener != nullptr)
		{
			if (!m_currentListener->IsActive() && !m_currentListener->IsDestroyed())
			{
				if (m_canPlay)
					DisableAudio();
				return;
			}

			if (m_currentListener->IsDestroyed())
			{
				SetCurrentListener();
				if (m_currentListener == nullptr)
				{
					Stop();
					return;
				}
			}

			if (!m_canPlay)
				EnableAudio();
			m_currentListener->Update();
			for (int i = 0; i < m_currentSourcesCount; ++i)
				m_audioSources[i].Update();
			m_audioEngine.update3dAudio();
		}
		else
		{
			if (m_canPlay)
				DisableAudio();
		}
	}

	void AudioSystem::Play()
	{
		if (m_paused)
			m_paused = false;
		ResetAudioSourcesPause();
		for (int i = 0; i < m_currentSourcesCount; ++i)
		{
			if (m_audioSources[i].IsActive() && m_audioSources[i].GetClip() != nullptr)
				m_audioSources[i].Play();
		}
	}

	void AudioSystem::SetPause(bool _pause)
	{
		m_paused = _pause;
		if (m_paused)
		{
			for (int i = 0; i < m_currentSourcesCount; ++i)
			{
				if (!m_audioSources[i].IsPaused() && m_audioSources[i].GetClip() != nullptr)
				{
					m_audioSources[i].Pause();
					m_audioSourcesToUnpause.push_back(&m_audioSources[i]);
				}
			}
		}
		else
		{
			for (int i = 0; i < m_audioSourcesToUnpause.size(); ++i)
			{
				if (m_audioSourcesToUnpause[i]->IsPaused())
					m_audioSourcesToUnpause[i]->Pause();
			}
			m_audioSourcesToUnpause.clear();
		}
	}

	void AudioSystem::Stop()
	{
		if (m_paused)
			m_paused = false;
		m_audioEngine.stopAll();
		ResetAudioSourcesPause();
	}

	void AudioSystem::PlayStartUp()
	{
		if (m_startupSound == nullptr)
			m_startupSound = Resource::ResourceManager::GetInstance().GetResource<Resource::AudioClip>("startup.mp3");
		if (m_startupSound == nullptr)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "Failed to load startup sound!");
			return;
		}
		m_audioEngine.play(*m_startupSound->GetAudio());
	}

	AudioSource* AudioSystem::AddAudioSource()
	{
		if (m_currentSourcesCount >= MAX_SIZE)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "Max audio source capacity reached, cannot add more!");
			return nullptr;
		}

		for (int i = 0; i < m_currentSourcesCount; ++i)
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

		m_audioSources[m_currentSourcesCount].~AudioSource();
		new (&m_audioSources[m_currentSourcesCount]) AudioSource(&m_audioEngine);
		m_audioSources[m_currentSourcesCount].SetActive(true);
		++m_currentSourcesCount;
		return &m_audioSources[m_currentSourcesCount - 1];
	}

	AudioListener* AudioSystem::AddAudioListener()
	{
		if (m_currentListenersCount >= MAX_LISTENER_SIZE)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "Max audio listener capacity reached, cannot add more!");
			return nullptr;
		}

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

	void AudioSystem::SetCurrentListener(AudioListener* _listener)
	{
		if (_listener == nullptr)
			return;

		m_currentListener = _listener;
		m_currentListener->Start();
	}

	void AudioSystem::SetCurrentListener()
	{
		if (m_currentListenersCount == 0)
			return;

		for (int i = 0; i < m_currentListenersCount; ++i)
		{
			if (!m_audioListeners[i].IsDestroyed() && m_audioListeners[i].IsActive())
			{
				m_currentListener = &m_audioListeners[i];
				m_currentListener->Start();
				return;
			}
		}
		m_currentListener = nullptr;
	}

	void AudioSystem::EditorUpdate()
	{
		m_stereoVolume[0] = m_audioEngine.getApproximateVolume(0);
		m_stereoVolume[1] = m_audioEngine.getApproximateVolume(1);
		if (m_currentListener != nullptr)
		{
			if (m_currentListener->IsActive())
				m_currentListener->Update();
			else
				m_audioEngine.set3dListenerParameters(0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f);
		}

		for (int i = 0; i < m_currentSourcesCount; ++i)
			m_audioSources[i].Update();
		m_audioEngine.update3dAudio();
	}

	AudioListener* AudioSystem::GetCurrentAudioListener() const
	{
		if (m_currentListener != nullptr)
		{
			if (!m_currentListener->IsDestroyed() && m_currentListener->IsActive())
				return m_currentListener;
		}
		return nullptr;
	}

	void AudioSystem::ResetAudioSourcesPause()
	{
		for (int i = 0; i < m_currentSourcesCount; ++i)
		{
			if (m_audioSources[i].IsPaused())
				m_audioSources[i].Pause();
		}
	}

	void AudioSystem::EnableAudio()
	{
		m_canPlay = true;
		if (m_currentListener != nullptr)
			m_currentListener->Start();
		else
			m_audioEngine.set3dListenerParameters(0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f);
		AudioSource::Enable();
		m_audioEngine.update3dAudio();
	}

	void AudioSystem::DisableAudio()
	{
		Stop();
		m_canPlay = false;
		AudioSource::Disable();
	}

	float AudioSystem::GetVolume() const
	{
		if (m_stereoVolume[0] > m_stereoVolume[1])
			return m_stereoVolume[0];
		else
			return m_stereoVolume[1];
	}

	void AudioSystem::SetMaxVolume(float _volume)
	{
		if (_volume < 0.f)
			_volume = 0.f;
		else if (_volume > 1.f)
			_volume = 1.f;

		m_audioEngine.setGlobalVolume(_volume);
	}

	std::vector<AudioSource*> AudioSystem::GetAudioSources()
	{
		std::vector<AudioSource*> sources{};
		for (int i = 0; i < m_currentSourcesCount; ++i)
		{
			if (!m_audioSources[i].IsDestroyed())
				sources.push_back(&m_audioSources[i]);
		}
		return sources;
	}

	SoLoud::Soloud* AudioSystem::GetAudioEngine()
	{
		return &m_audioEngine;
	}

	void AudioSystem::Reset()
	{
		m_currentSourcesCount = 0;
		m_currentListenersCount = 0;
		m_currentListener = nullptr;
	}
}