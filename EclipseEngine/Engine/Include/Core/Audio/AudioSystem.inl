#include "AudioSystem.hpp"

namespace Core
{
	inline void AudioSystem::Destroy() { m_audioEngine.deinit(); }
	inline bool AudioSystem::IsPaused() const { return m_paused; }
	inline bool AudioSystem::IsAudioEnabled() const { return m_canPlay; }
	inline float* AudioSystem::GetStereoVolume() { return m_stereoVolume; }
	inline float AudioSystem::GetMaxVolume() { return m_audioEngine.getGlobalVolume(); }
}