#pragma once
#include "ProjectExports.hpp"
#include "soloud.h"
#include "soloud_wav.h"

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

	private:
		SoLoud::Soloud m_audioEngine{};
		SoLoud::Wav m_startupSound{};
	};
}