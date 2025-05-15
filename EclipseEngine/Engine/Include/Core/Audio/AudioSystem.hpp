#pragma once
#include "ProjectExports.hpp"
#include "soloud.h"
#include "soloud_wav.h"
#include "AudioSource.hpp"
#include "AudioListener.hpp"
#include <vector>

namespace Resource
{
	class AudioClip;
}

namespace Core
{
	class AudioSystem
	{
	public:
		ECLIPSE_ENGINE AudioSystem() = default;
		ECLIPSE_ENGINE ~AudioSystem();

		ECLIPSE_ENGINE void Init();
		ECLIPSE_ENGINE void Start();
		ECLIPSE_ENGINE void Destroy();
		ECLIPSE_ENGINE void Update();
		ECLIPSE_ENGINE void Play();
		ECLIPSE_ENGINE void SetPause(bool _pause);
		ECLIPSE_ENGINE bool IsPaused() const;
		ECLIPSE_ENGINE void Stop();

		ECLIPSE_ENGINE void PlayStartUp();
		ECLIPSE_ENGINE AudioSource* AddAudioSource();
		ECLIPSE_ENGINE AudioListener* AddAudioListener();
		ECLIPSE_ENGINE void SetCurrentListener(AudioListener* _listener);
		ECLIPSE_ENGINE void SetCurrentListener();
		ECLIPSE_ENGINE void EditorUpdate();
		ECLIPSE_ENGINE AudioListener* GetCurrentAudioListener() const;
		ECLIPSE_ENGINE void EnableAudio();
		ECLIPSE_ENGINE void DisableAudio();
		ECLIPSE_ENGINE bool IsAudioEnabled() const;
		ECLIPSE_ENGINE float* GetStereoVolume();
		ECLIPSE_ENGINE float GetVolume() const;
		ECLIPSE_ENGINE float GetMaxVolume();
		ECLIPSE_ENGINE void SetMaxVolume(float _volume);
		ECLIPSE_ENGINE std::vector<AudioSource*> GetAudioSources();
		ECLIPSE_ENGINE SoLoud::Soloud* GetAudioEngine();
		ECLIPSE_ENGINE void DeleteChannel(std::string _name);

		ECLIPSE_ENGINE void Reset();

		ECLIPSE_ENGINE void SerializeChannels(std::string _filePath);
		ECLIPSE_ENGINE void DeserializeChannels(std::string _filePath);

	private:
		void ResetAudioSourcesPause();

		static const int MAX_SIZE = 100;
		int m_currentSourcesCount = 0;
		AudioSource m_audioSources[MAX_SIZE];
		std::vector<AudioSource*> m_audioSourcesToUnpause{};

		static const int MAX_LISTENER_SIZE = 5;
		int m_currentListenersCount = 0;
		AudioListener m_audioListeners[MAX_LISTENER_SIZE];
		AudioListener* m_currentListener = nullptr;

		SoLoud::Soloud m_audioEngine{};
		Resource::AudioClip* m_startupSound{};

		bool m_canPlay = true;
		bool m_paused = false;
		float m_stereoVolume[2] = { 0.f, 0.f };
	};
}

#include "AudioSystem.inl"