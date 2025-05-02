#include "Audio/AudioSource.hpp"
#include "Logger.hpp"
#include "Maths.hpp"

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
		{
			if (m_paused)
				Pause();
			m_audioEngine->stop(m_sound);
		}

		m_sound = m_audioEngine->play(m_audioClip->audioFile);
		m_audioEngine->setLooping(m_sound, m_looping);
	}

	void AudioSource::Pause()
	{
		if (m_audioClip == nullptr)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "No audio clip to pause!");
			return;
		}
		m_paused = !m_paused;
		m_audioEngine->setPause(m_sound, m_paused);
	}

	void AudioSource::Stop()
	{
		if(m_audioClip == nullptr)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "No audio clip to stop!");
			return;
		}
		if (m_paused)
			Pause();
		m_audioEngine->stop(m_sound);
	}

	void AudioSource::SetClip(Resource::AudioClip* _clip)
	{
		m_audioClip = _clip;
		if(m_audioClip == nullptr)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Failed to set audio clip!");
			return;
		}
		m_audioClipLength = m_audioClip->GetLength();
	}

	Resource::AudioClip* AudioSource::GetClip() 
	{
		return m_audioClip;
	}

	void AudioSource::SetLooping(bool _looping)
	{
		m_looping = _looping;
	}

	float* AudioSource::GetData() const
	{
		if (m_audioClip == nullptr)
			return nullptr;
		return m_audioClip->audioFile.mData;
	}

	int AudioSource::GetSampleCount() const
	{
		if (m_audioClip == nullptr)
			return 0;
		return m_audioClip->audioFile.mSampleCount;
	}

	float AudioSource::GetTime() const
	{
		if (m_audioClip == nullptr)
			return 0.0;
		
		return static_cast<float>(m_audioEngine->getStreamPosition(m_sound));
	}

	float AudioSource::GetLength() const
	{
		if (m_audioClip == nullptr)
			return 0.f;
		return m_audioClipLength;
	}

	void AudioSource::SetTime(float _time)
	{
		if (m_audioClip == nullptr)
			return;

		if (_time < 0.f)
		{
			m_audioEngine->seek(m_sound, _time);
			return;
		}
	
		if (_time > m_audioClipLength)
		{
			m_audioEngine->seek(m_sound, m_audioClipLength);
			return;
		}

		m_audioEngine->seek(m_sound, _time);
	}

	bool AudioSource::IsPlaying() const
	{
		if (m_audioClip == nullptr)
			return false;

		return m_audioEngine->isValidVoiceHandle(m_sound);
	}
}