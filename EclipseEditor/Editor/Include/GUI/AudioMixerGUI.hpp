#pragma once
#include <imgui.h>
#include <implot.h>
#include <vector>

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

		void Draw(Core::AudioSystem* _audioSystem, float _deltaTime);

	private:
		Resource::Texture* m_playBtnTexture = nullptr;
		Resource::Texture* m_stopBtnTexture = nullptr;
		Resource::Texture* m_pauseBtnTexture = nullptr;

		float m_timer = 0.f;
		/// <summary>
		/// refresh rate in seconds
		/// </summary>
		float m_refreshRate = 0.005f;
		std::vector<float> m_values{};
		const float MAX_TIME = 4.f;
		const int NB_VALUES = 100;
	};
}