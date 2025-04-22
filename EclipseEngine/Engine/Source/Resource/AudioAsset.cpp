#include "AudioAsset.hpp"

namespace Resource
{
	void AudioAsset::Load(std::string _path)
	{
		m_audioFile.load(_path);
	}
}