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
		uintmax_t size = std::filesystem::file_size(_path);
		// If size is bigger than 10MB, we use a stream instead of loading directly in memory
		if (size >= 10000000)
		{
			m_isStream = true;
			m_audioStream.load(_path.c_str());
			m_length = static_cast<float>(m_audioStream.getLength());
			// We don't kill inaudible sounds to leave room for runtime volume changes (e.g when the player gets closer to the source)
			m_audioStream.setInaudibleBehavior(true, false);
		}
		else
		{
			m_audioFile.load(_path.c_str());
			m_length = static_cast<float>(m_audioFile.getLength());
			// We don't kill inaudible sounds to leave room for runtime volume changes (e.g when the player gets closer to the source)
			m_audioFile.setInaudibleBehavior(true, false);
		}
	}

	void AudioClip::Delete()
	{
	}

	SoLoud::AudioSource* AudioClip::GetAudio()
	{
		if (m_isStream)
			return &m_audioStream;
		else
			return &m_audioFile;
	}

	int AudioClip::GetSampleCount() const
	{
		if (m_isStream)
			return m_audioStream.mSampleCount;
		else
			return m_audioFile.mSampleCount;
	}

	float* AudioClip::GetData()
	{
		if (m_isStream)
			return nullptr;
		else
			return m_audioFile.mData;
	}
}