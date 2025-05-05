#pragma once
#include "Audio/AudioSource.hpp"

namespace Core
{
	inline bool AudioSource::IsLooping() const { return m_looping; }
	inline bool AudioSource::IsPaused() const { return m_paused; }
	inline float AudioSource::GetSampleRate() const { return m_sampleRate; }
	inline bool AudioSource::Is3D() const { return m_3D; }
	inline float AudioSource::GetMinDistance() const { return m_minDistance; }
	inline float AudioSource::GetMaxDistance() const { return m_maxDistance; }
	inline bool AudioSource::IsPlayingOnAwake() const { return m_playOnAwake; }
}