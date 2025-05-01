#pragma once
#include "ProjectExports.hpp"
#include "soloud.h"
#include "soloud_wav.h"
#include "AudioSource.hpp"

namespace Core
{
	class AudioSystem
	{
	public:
		ECLIPSE_ENGINE AudioSystem() = default;
		ECLIPSE_ENGINE ~AudioSystem() = default;

		ECLIPSE_ENGINE void Init();
		ECLIPSE_ENGINE void Destroy();

		ECLIPSE_ENGINE void PlayStartUp();
		ECLIPSE_ENGINE AudioSource* Add();

	private:
		static const int MAX_SIZE = 100;
		int m_currentCount = 0;
		AudioSource m_audioEmitters[MAX_SIZE];

		SoLoud::Soloud m_audioEngine{};
		SoLoud::Wav m_startupSound{};
	};
}