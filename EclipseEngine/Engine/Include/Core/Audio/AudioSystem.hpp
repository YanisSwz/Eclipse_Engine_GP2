#pragma once
#include "ProjectExports.hpp"
#include "soloud.h"
#include "soloud_wav.h"
#include "AudioSource.hpp"
#include "AudioListener.hpp"

namespace Core
{
	class AudioSystem
	{
	public:
		ECLIPSE_ENGINE AudioSystem() = default;
		ECLIPSE_ENGINE ~AudioSystem() = default;

		ECLIPSE_ENGINE void Init();
		ECLIPSE_ENGINE void Destroy();
		ECLIPSE_ENGINE void Update();
		ECLIPSE_ENGINE void SetPause(bool _pause);
		ECLIPSE_ENGINE void Stop();

		ECLIPSE_ENGINE void PlayStartUp();
		ECLIPSE_ENGINE AudioSource* AddAudioSource();
		ECLIPSE_ENGINE AudioListener* AddAudioListener();
		ECLIPSE_ENGINE void SetCurrentListener(AudioListener* _listener);
		ECLIPSE_ENGINE void SetCurrentListener();
		ECLIPSE_ENGINE AudioListener* GetCurrentAudioListener() const;

	private:
		static const int MAX_SIZE = 100;
		int m_currentCount = 0;
		AudioSource m_audioSources[MAX_SIZE];

		static const int MAX_LISTENER_SIZE = 5;
		int m_currentListenersCount = 0;
		AudioListener m_audioListeners[MAX_LISTENER_SIZE];
		AudioListener* m_currentListener = nullptr;

		SoLoud::Soloud m_audioEngine{};
		SoLoud::Wav m_startupSound{};

		bool m_canPlay = true;
	};
}