#pragma once
#include "Resource/IResource.hpp"
#include "soloud_wav.h"
#include "soloud_wavstream.h"
#include <filesystem>

namespace Resource
{
	class AudioClip : public IResource
	{
	public:
		ECLIPSE_ENGINE AudioClip(std::string _name = "");
		ECLIPSE_ENGINE ~AudioClip() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path) override;
		ECLIPSE_ENGINE void Delete() override;
		
		ECLIPSE_ENGINE inline float GetLength() const { return m_length; }
		ECLIPSE_ENGINE SoLoud::AudioSource* GetAudio();
		ECLIPSE_ENGINE int GetSampleCount() const;
		ECLIPSE_ENGINE float* GetData();
		ECLIPSE_ENGINE inline bool IsStream() const { return m_isStream; }

	private:
		bool m_isStream = false;
		float m_length = 0.f;
		SoLoud::Wav m_audioFile;
		SoLoud::WavStream m_audioStream;
	};
}