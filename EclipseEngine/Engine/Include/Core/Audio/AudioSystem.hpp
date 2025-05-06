#pragma once
#include "ProjectExports.hpp"
#include "soloud.h"
#include "soloud_wav.h"
#include "AudioSource.hpp"
#include "AudioListener.hpp"
#include <vector>

namespace Core
{
	class AudioSystem
	{
	public:
		ECLIPSE_ENGINE AudioSystem() = default;
		ECLIPSE_ENGINE ~AudioSystem() = default;

		ECLIPSE_ENGINE void Init();
		ECLIPSE_ENGINE void Start();
		ECLIPSE_ENGINE void Destroy();
		ECLIPSE_ENGINE void Update();
		ECLIPSE_ENGINE void SetPause(bool _pause);
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
		ECLIPSE_ENGINE inline bool IsAudioEnabled() const { return m_canPlay; }
		ECLIPSE_ENGINE inline float* GetStereoVolume() { return m_stereoVolume; }
		ECLIPSE_ENGINE float GetVolume() const;
		ECLIPSE_ENGINE inline float GetMaxVolume() { return m_audioEngine.getGlobalVolume(); }
		ECLIPSE_ENGINE void SetMaxVolume(float _volume);

	private:
		void ResetAudioSourcesPause();

		static const int MAX_SIZE = 100;
		int m_currentCount = 0;
		AudioSource m_audioSources[MAX_SIZE];
		std::vector<AudioSource*> m_audioSourcesToUnpause{};

		static const int MAX_LISTENER_SIZE = 5;
		int m_currentListenersCount = 0;
		AudioListener m_audioListeners[MAX_LISTENER_SIZE];
		AudioListener* m_currentListener = nullptr;

		SoLoud::Soloud m_audioEngine{};
		SoLoud::Wav m_startupSound{};

		bool m_canPlay = true;
		float m_stereoVolume[2] = { 0.f, 0.f };
	};
}