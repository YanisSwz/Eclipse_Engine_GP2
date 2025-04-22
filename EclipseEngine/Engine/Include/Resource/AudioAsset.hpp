#pragma once
#include "Audiofile.h"
#include "ProjectExports.hpp"
#include <string>

namespace Resource
{
	class AudioAsset
	{
	public:
		ECLIPSE_ENGINE AudioAsset() = default;
		ECLIPSE_ENGINE ~AudioAsset() = default;

		ECLIPSE_ENGINE void Load(std::string _path);

		AudioFile<double> m_audioFile;
	private:
	};
}