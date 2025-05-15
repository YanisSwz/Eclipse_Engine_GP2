#pragma once
#include "Core/Component.hpp"
#include "ProjectExports.hpp"
#include "soloud.h"
#include "Resource/AudioClip.hpp"
#include <unordered_map>
#include <utility>
#include <string>

namespace Core
{
	class AudioSource : public Component
	{
	public:
		ECLIPSE_ENGINE AudioSource() = default;
		ECLIPSE_ENGINE AudioSource(SoLoud::Soloud* _audioEngine);
		ECLIPSE_ENGINE ~AudioSource() = default;

		ECLIPSE_ENGINE void SetActive(bool _activate) override;
		ECLIPSE_ENGINE void Destroy() override;

		ECLIPSE_ENGINE void Update();
		ECLIPSE_ENGINE void UpdateChannel();
		ECLIPSE_ENGINE void Play();
		/// <summary>
		/// Pause/Unpause the sound
		/// </summary>
		/// <returns></returns>
		ECLIPSE_ENGINE void Pause();
		ECLIPSE_ENGINE void Stop();
		ECLIPSE_ENGINE void SetClip(Resource::AudioClip* _clip);
		ECLIPSE_ENGINE Resource::AudioClip* GetClip();
		ECLIPSE_ENGINE inline std::string GetClipName() const { return (m_audioClip) ? m_audioClip->name : ""; }
		ECLIPSE_ENGINE void SetLooping(bool _looping);
		ECLIPSE_ENGINE bool IsLooping() const;
		ECLIPSE_ENGINE float* GetData() const;
		ECLIPSE_ENGINE int GetSampleCount() const;
		ECLIPSE_ENGINE float GetTime() const;
		ECLIPSE_ENGINE float GetLength() const;
		ECLIPSE_ENGINE void SetTime(float _time);
		ECLIPSE_ENGINE bool IsPlaying() const;
		ECLIPSE_ENGINE bool IsPaused() const;
		ECLIPSE_ENGINE void SetMaxVolume(float _vol);
		ECLIPSE_ENGINE float GetMaxVolume() const;
		ECLIPSE_ENGINE float GetSampleRate() const;
		ECLIPSE_ENGINE void SetSampleRate(float _rate);
		ECLIPSE_ENGINE float GetPan() const;
		ECLIPSE_ENGINE void SetPan(float _pan);
		ECLIPSE_ENGINE bool Is3D() const;
		ECLIPSE_ENGINE void Set3D(bool _is3D);
		ECLIPSE_ENGINE float GetMinDistance() const;
		ECLIPSE_ENGINE float GetMaxDistance() const;
		ECLIPSE_ENGINE void SetMinDistance(float _min);
		ECLIPSE_ENGINE void SetMaxDistance(float _max);
		ECLIPSE_ENGINE void SetPlayOnAwake(bool _play);
		ECLIPSE_ENGINE bool IsPlayingOnAwake() const;
		ECLIPSE_ENGINE void SetChannel(std::string _name);

		ECLIPSE_ENGINE static void Enable();
		ECLIPSE_ENGINE static void Disable();
		ECLIPSE_ENGINE static void AddChannel(std::string _name, SoLoud::handle _handle, float _volume = 1.f);
		ECLIPSE_ENGINE static std::vector<std::string> GetChannelNames();
		ECLIPSE_ENGINE static std::vector<SoLoud::handle> GetChannelHandles();
		ECLIPSE_ENGINE static std::unordered_map<std::string, std::pair<SoLoud::handle, float>>* GetChannels();

		ECLIPSE_ENGINE void Serialize(json& _j) override;
		ECLIPSE_ENGINE void Deserialize(const json& _j) override;

		std::string channel = "SFX";
	private:
		static bool m_audioEnabled;
		static std::unordered_map<std::string, std::pair<SoLoud::handle, float>> m_audioChannels;
		bool m_looping = false;
		bool m_playOnAwake = true;
		bool m_paused = false;
		bool m_3D = false;
		/// <summary>
		/// boolean for looping streams to avoid playing all the time
		/// </summary>
		bool m_isPlaying = false;
		float m_audioClipLength = 0.f;
		float m_volume = 1.f;
		/// <summary>
		/// Volume of voice group
		/// </summary>
		float m_channelVolume = 1.f;
		float m_sampleRate = 0.f;
		float m_pan = 0.f;
		float m_minDistance = 1.f;
		float m_maxDistance = 5.f;
		SoLoud::Soloud* m_audioEngine = nullptr;
		Resource::AudioClip* m_audioClip = nullptr;
		SoLoud::handle m_sound;
	};
}

#include "AudioSource.inl"