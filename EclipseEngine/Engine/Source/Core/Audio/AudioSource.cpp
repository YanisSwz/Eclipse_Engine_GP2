#include "Audio/AudioSource.hpp"
#include "Logger.hpp"

namespace Core
{
	AudioSource::AudioSource(SoLoud::Soloud* _audioEngine)
	{
		m_audioEngine = _audioEngine;
	}

	void AudioSource::Play()
	{
		if(m_audioClip == nullptr)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "No audio clip to play!");
			return;
		}
		// If a sound is already playing, stop it
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			m_audioEngine->stop(m_sound);
		m_sound = m_audioEngine->play(m_audioClip->audioFile);
	}

	void AudioSource::Stop()
	{
		if(m_audioClip == nullptr)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "No audio clip to stop!");
			return;
		}
		m_audioClip->audioFile.stop();
	}

	void AudioSource::SetClip(Resource::AudioClip* _clip)
	{
		m_audioClip = _clip;
	}

	Resource::AudioClip* AudioSource::GetClip() 
	{
		return m_audioClip;
	}

	void AudioSource::SetLooping(bool _looping)
	{
		if (m_audioClip == nullptr)
			return;
		m_looping = _looping;
		m_audioClip->audioFile.setLooping(m_looping);
	}
}