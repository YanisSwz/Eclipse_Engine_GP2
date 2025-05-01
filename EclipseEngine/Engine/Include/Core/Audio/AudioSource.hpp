#pragma once
#include "Core/Component.hpp"
#include "ProjectExports.hpp"
#include "soloud.h"
#include "Resource/AudioClip.hpp"

namespace Core
{
	class AudioSource : public Component
	{
	public:
		ECLIPSE_ENGINE AudioSource() = default;
		ECLIPSE_ENGINE AudioSource(SoLoud::Soloud* _audioEngine);
		ECLIPSE_ENGINE ~AudioSource() = default;

		ECLIPSE_ENGINE void Play();
		ECLIPSE_ENGINE void Stop();
		ECLIPSE_ENGINE void SetClip(Resource::AudioClip* _clip);
		ECLIPSE_ENGINE Resource::AudioClip* GetClip();
		ECLIPSE_ENGINE void SetLooping(bool _looping);
		ECLIPSE_ENGINE inline bool GetLooping() const { return m_looping; };

	private:
		bool m_looping = false;
		SoLoud::Soloud* m_audioEngine = nullptr;
		Resource::AudioClip* m_audioClip = nullptr;
		SoLoud::handle m_sound;
	};
}