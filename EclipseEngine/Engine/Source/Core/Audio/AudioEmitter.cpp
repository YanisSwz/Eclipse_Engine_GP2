#include "Audio/AudioEmitter.hpp"
#include "Logger.hpp"

namespace Core
{
	AudioEmitter::AudioEmitter(SoLoud::Soloud* _audioEngine)
	{
		m_audioEngineRef = _audioEngine;
	}

	void AudioEmitter::Play()
	{
		if(m_audioClip == nullptr)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "No audio clip to play!");
			return;
		}
		m_audioEngineRef->play(*m_audioClip);
	}


}