#include "Audio/AudioSource.hpp"
#include "Logger.hpp"
#include "Maths.hpp"
#include "GameObject.hpp"

namespace Core
{
	bool AudioSource::m_audioEnabled = true;

	AudioSource::AudioSource(SoLoud::Soloud* _audioEngine)
	{
		m_audioEngine = _audioEngine;
	}

	void AudioSource::SetActive(bool _active)
	{
		m_active = _active;
		if (!m_active)
		{
			if (m_audioEngine->isValidVoiceHandle(m_sound) && !m_paused)
				Pause();
		}
		else
		{
			if (m_audioEngine->isValidVoiceHandle(m_sound) && m_paused)
				Pause();
		}
	}

	void AudioSource::Destroy()
	{
		Stop();
		m_active = false;
		m_destroyed = true;
	}

	void AudioSource::Update() 
	{
		if (m_destroyed || !m_active)
			return;

		if (!m_3D)
			return;

		if (!m_audioEngine->isValidVoiceHandle(m_sound))
			return;

		if (!m_gameObject->transform->HasPositionChanged())
			return;

		Math::Vec3 newPos = m_gameObject->transform->GetPosition();
		m_audioEngine->set3dSourcePosition(m_sound, newPos.x, newPos.y, newPos.z);
	}

	void AudioSource::Play()
	{
		if (!m_audioEnabled)
			return;

		if (m_audioClip == nullptr)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "No audio clip to play!");
			return;
		}
		if(m_volume <= Math::Tools::epsilon)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "Prevented clip with 0 volume to play");
			return;
		}
		// If a sound is already playing, stop it 
		if (m_audioEngine->isValidVoiceHandle(m_sound))
		{
			if (m_paused)
				Pause();
			m_audioEngine->stop(m_sound);
		}

		if (!m_3D)
		{
			m_sound = m_audioEngine->play(m_audioClip->audioFile, m_volume);
			m_audioEngine->setPan(m_sound, m_pan);
		}
		else
		{
			Math::Vec3 pos = m_gameObject->transform->GetPosition();
			m_sound = m_audioEngine->play3d(m_audioClip->audioFile, pos.x, pos.y, pos.z, 0.f, 0.f, 0.f, m_volume, true);
			m_audioEngine->set3dSourceMinMaxDistance(m_sound, m_minDistance, m_maxDistance);
			m_audioEngine->set3dSourceAttenuation(m_sound, SoLoud::AudioSource::ATTENUATION_MODELS::LINEAR_DISTANCE, 1.f);
			m_audioEngine->setPause(m_sound, false);
		}
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
		if(m_audioEngine->isValidVoiceHandle(m_sound))
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
		else if (_time > m_audioClipLength)
			_time = m_audioClipLength;

		m_audioEngine->seek(m_sound, _time);
	}

	bool AudioSource::IsPlaying() const
	{
		if (m_audioClip == nullptr)
			return false;

		return m_audioEngine->isValidVoiceHandle(m_sound);
	}

	void AudioSource::SetMaxVolume(float _vol)
	{
		if (_vol < 0.f)
		{
			m_volume = 0.f;
			return;
		}
		else if (_vol > 1.f)
		{
			m_volume = 1.f;
			return;
		}

		m_volume = _vol;
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			m_audioEngine->setVolume(m_sound, m_volume);
	}

	void AudioSource::SetSampleRate(float _rate)
	{
		if(_rate < 8000.f)
			_rate = 8000.f;
		else if (_rate > 96000.f)
			_rate = 96000.f;

		float ratio = m_sampleRate / _rate;
		m_sampleRate = _rate;
		m_audioClipLength *= ratio;
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			m_audioEngine->setSamplerate(m_sound, m_sampleRate);
	}

	void AudioSource::SetPan(float _pan)
	{
		if (_pan < -1.f)
			_pan = -1.f;
		else if (_pan > 1.f)
			_pan = 1.f;

		m_pan = _pan;
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			m_audioEngine->setPan(m_sound, m_pan);
	}

	void AudioSource::SetMinDistance(float _min)
	{
		if (_min < 0.1f)
			_min = 0.1f;
		else if (_min > m_maxDistance)
			_min = m_maxDistance;

		m_minDistance = _min;
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			m_audioEngine->set3dSourceMinMaxDistance(m_sound, m_minDistance, m_maxDistance);
	}

	void AudioSource::SetMaxDistance(float _max)
	{
		if (_max < m_minDistance)
			_max = m_minDistance;

		m_maxDistance = _max;
		if (m_audioEngine->isValidVoiceHandle(m_sound))
			m_audioEngine->set3dSourceMinMaxDistance(m_sound, m_minDistance, m_maxDistance);
	}

	void AudioSource::Enable()
	{
		m_audioEnabled = true;
	}

	void AudioSource::Disable()
	{
		m_audioEnabled = false;
	}

	float* AudioSource::GetStereoVolume()
	{
		if (m_audioClip == nullptr || !m_audioEngine->isValidVoiceHandle(m_sound))
		{
			m_stereoVolume[0] = 0.f;
			m_stereoVolume[1] = 0.f;
			return m_stereoVolume;
		}

		int sign = Math::Tools::Sign(m_pan);
		float volume = 0.f;
		float pan = 0.f;
		if (!m_3D)
		{
			volume = m_audioEngine->getVolume(m_sound);
			pan = m_pan;
		}
		else
		{
			volume = m_audioEngine->getOverallVolume(m_sound);
			pan = m_audioEngine->getPan(m_sound);
		}
		if(sign == 0)
		{
			m_stereoVolume[0] = volume;
			m_stereoVolume[1] = volume;
		}
		else if (sign == 1)
		{
			m_stereoVolume[0] = volume * (1.f - pan);
			m_stereoVolume[1] = volume + pan * volume;
		}
		else if (sign == -1)
		{
			m_stereoVolume[0] = volume + (-pan) * volume;
			m_stereoVolume[1] = volume * (1.f + pan);
		}
		return m_stereoVolume;
	}

	float AudioSource::GetVolume() const 
	{
		if (m_stereoVolume[0] > m_stereoVolume[1])
			return m_stereoVolume[0];
		else
			return m_stereoVolume[1];
	}
}