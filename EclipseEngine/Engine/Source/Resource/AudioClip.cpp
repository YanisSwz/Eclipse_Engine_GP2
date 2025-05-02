#include "Resource/AudioClip.hpp"

namespace Resource
{
	AudioClip::AudioClip(std::string _name)
	{
		name = _name;
	}

	AudioClip::~AudioClip()
	{
	}

	void AudioClip::GetFileContent(std::string _path)
	{
		audioFile.load(_path.c_str());
		m_length = static_cast<float>(audioFile.getLength());
	}

	void AudioClip::Delete()
	{
	}
}