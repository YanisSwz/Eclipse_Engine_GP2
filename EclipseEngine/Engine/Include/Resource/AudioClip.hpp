#pragma once
#include "Resource/IResource.hpp"
#include "soloud_wav.h"

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

		SoLoud::Wav audioFile;
	private:
		float m_length = 0.f;
	};
}