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
	inline void AudioSource::SetPlayOnAwake(bool _play) { m_playOnAwake = _play; }
	inline void AudioSource::Set3D(bool _is3D) { m_3D = _is3D; }
	inline float AudioSource::GetPan() const { return m_pan; }
	inline float AudioSource::GetVolume() const { return m_volume; }
	inline Resource::AudioClip* AudioSource::GetClip() { return m_audioClip; }
}