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
		m_audioEngine->play(m_audioClip->audioFile);
	}

	void AudioSource::SetClip(Resource::AudioClip* _clip)
	{
		m_audioClip = _clip;
	}

	Resource::AudioClip* AudioSource::GetClip() 
	{
		return m_audioClip;
	}
}