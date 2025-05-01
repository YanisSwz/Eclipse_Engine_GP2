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
	}

	void AudioClip::Delete()
	{
	}
}