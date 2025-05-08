#pragma once
#include <imgui.h>

namespace Core
{
	class AudioSystem;
}

namespace Resource
{
	class Texture;
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
		Resource::Texture* m_playBtnTexture = nullptr;
		Resource::Texture* m_stopBtnTexture = nullptr;
		Resource::Texture* m_pauseBtnTexture = nullptr;
	};
}