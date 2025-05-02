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
		if (m_audioClip == nullptr)
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

		m_sound = m_audioEngine->play(m_audioClip->audioFile, m_volume);
		m_audioEngine->setLooping(m_sound, m_looping);
		m_audioEngine->setSamplerate(m_sound, m_sampleRate);
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
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			Stop();
		m_audioClip = _clip;
		if(m_audioClip == nullptr)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Failed to set audio clip!");
			return;
		}
		m_audioClipLength = m_audioClip->GetLength();
		m_sampleRate = m_audioClip->audioFile.mSampleCount / m_audioClip->GetLength();
	}

	Resource::AudioClip* AudioSource::GetClip()
	{
		return m_audioClip;
	}

	void AudioSource::SetLooping(bool _looping)
	{
		m_looping = _looping;
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			m_audioEngine->setLooping(m_sound, m_looping);
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
			return 0.f;

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
		if (m_audioClip == nullptr || !m_audioEngine->isValidVoiceHandle(m_sound))
			return;

		if (_time < 0.f)
			_time = 0.f;

		if (_time > m_audioClipLength)
			_time = m_audioClipLength;

		m_audioEngine->seek(m_sound, _time);
	}

	bool AudioSource::IsPlaying() const
	{
		if (m_audioClip == nullptr)
			return false;

		return m_audioEngine->isValidVoiceHandle(m_sound);
	}

	void AudioSource::SetVolume(float _vol)
	{
		if (_vol < 0.f)
		{
			m_volume = 0.f;
			return;
		}

		if (_vol > 1.f)
		{
			m_volume = 1.f;
			return;
		}

		m_volume = _vol;
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			m_audioEngine->setVolume(m_sound, m_volume);
	}

	float AudioSource::GetVolume() const
	{
		return m_volume;
	}

	void AudioSource::SetSampleRate(float _rate)
	{
		if(_rate < 8000.f)
			_rate = 8000.f;

		if (_rate > 48000.f)
			_rate = 48000.f;

		float ratio = m_sampleRate / _rate;
		m_sampleRate = _rate;
		m_audioClipLength *= ratio;
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			m_audioEngine->setSamplerate(m_sound, m_sampleRate);
	}
}