#pragma once
#include <imgui.h>

namespace Core
{
	class AudioSystem;
}

namespace GUI
{
	class AudioMixerGUI
	{
	public:
		AudioMixerGUI();
		~AudioMixerGUI() = default;

		void Draw(Core::AudioSystem* _audioSystem);

	private:
	};
}