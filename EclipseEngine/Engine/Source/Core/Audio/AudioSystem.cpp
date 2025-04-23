#include "Audio/AudioSystem.hpp"

namespace Core
{
	void AudioSystem::Init()
	{
		m_audioEngine.init();

		m_startupSound.load("Assets/Audio/startup.mp3");
		m_startupSound.setVolume(2.f);
	}

	void AudioSystem::Destroy()
	{
		m_audioEngine.deinit();
	}

	void AudioSystem::PlayStartUp()
	{
		m_audioEngine.play(m_startupSound);
	}
}