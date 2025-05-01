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

		SoLoud::Wav audioFile;
	private:
	};
}