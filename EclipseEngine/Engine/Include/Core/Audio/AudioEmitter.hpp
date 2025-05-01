#pragma once
#include "Core/Component.hpp"
#include "ProjectExports.hpp"
#include "soloud.h"
#include "soloud_wav.h"

namespace Core
{
	class AudioEmitter : public Component
	{
	public:
		ECLIPSE_ENGINE AudioEmitter() = default;
		ECLIPSE_ENGINE AudioEmitter(SoLoud::Soloud* _audioEngine);
		ECLIPSE_ENGINE ~AudioEmitter() = default;

		ECLIPSE_ENGINE void Play();

	private:
		SoLoud::Soloud* m_audioEngineRef = nullptr;
		SoLoud::Wav* m_audioClip = nullptr;
	};
}