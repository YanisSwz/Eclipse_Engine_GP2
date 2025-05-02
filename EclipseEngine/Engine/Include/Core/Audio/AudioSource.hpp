#pragma once
#include "Core/Component.hpp"
#include "ProjectExports.hpp"
#include "soloud.h"
#include "Resource/AudioClip.hpp"

namespace Core
{
	class AudioSource : public Component
	{
	public:
		ECLIPSE_ENGINE AudioSource() = default;
		ECLIPSE_ENGINE AudioSource(SoLoud::Soloud* _audioEngine);
		ECLIPSE_ENGINE ~AudioSource() = default;

		ECLIPSE_ENGINE void SetActive(bool _activate) override;

		ECLIPSE_ENGINE void Play();
		/// <summary>
		/// Pause/Unpause the sound
		/// </summary>
		/// <returns></returns>
		ECLIPSE_ENGINE void Pause();
		ECLIPSE_ENGINE void Stop();
		ECLIPSE_ENGINE void SetClip(Resource::AudioClip* _clip);
		ECLIPSE_ENGINE Resource::AudioClip* GetClip();
		ECLIPSE_ENGINE void SetLooping(bool _looping);
		ECLIPSE_ENGINE inline bool GetLooping() const { return m_looping; };
		ECLIPSE_ENGINE inline bool GetPause() const { return m_paused; }
		ECLIPSE_ENGINE float* GetData() const;
		ECLIPSE_ENGINE int GetSampleCount() const;
		ECLIPSE_ENGINE float GetTime() const;
		ECLIPSE_ENGINE float GetLength() const;
		ECLIPSE_ENGINE void SetTime(float _time);
		ECLIPSE_ENGINE bool IsPlaying() const;
		ECLIPSE_ENGINE void SetVolume(float _vol);
		ECLIPSE_ENGINE float GetVolume() const;
		ECLIPSE_ENGINE inline float GetSampleRate() const { return m_sampleRate; };
		ECLIPSE_ENGINE void SetSampleRate(float _rate);
		ECLIPSE_ENGINE float GetPan() const;
		ECLIPSE_ENGINE void SetPan(float _pan);

	private:
		bool m_looping = false;
		bool m_paused = false;
		float m_audioClipLength = 0.f;
		float m_volume = 1.f;
		float m_sampleRate = 0.f;
		float m_pan = 0.f;
		SoLoud::Soloud* m_audioEngine = nullptr;
		Resource::AudioClip* m_audioClip = nullptr;
		SoLoud::handle m_sound;
	};
}