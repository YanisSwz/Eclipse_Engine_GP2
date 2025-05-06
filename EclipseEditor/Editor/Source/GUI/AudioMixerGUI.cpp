#include "GUI/AudioMixerGUI.hpp"
#include "Core/Scene.hpp"
#include "Core/Audio/AudioSystem.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"

namespace GUI
{
	AudioMixerGUI::AudioMixerGUI(){}

	void AudioMixerGUI::Draw(Core::AudioSystem* _audioSystem)
	{
		ImGui::SetNextWindowSizeConstraints({ 300.f, 300.f }, ImGui::GetMainViewport()->Size);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin("Audio Mixer", 0, ImGuiWindowFlags_HorizontalScrollbar);

		float volume = _audioSystem->GetMaxVolume();
		if (GUI::AudioChannel("Master", _audioSystem->GetStereoVolume(), &volume, ImVec2(50, ImGui::GetWindowHeight() / 1.5f)))
			_audioSystem->SetMaxVolume(volume);

		std::vector<Core::AudioSource*> channels = _audioSystem->GetAudioSources();
		for(int i = 0; i < channels.size(); ++i)
		{
			ImGui::SameLine();
			GUI::AudioChannel(channels[i]->GetGameObject()->name.c_str(), channels[i]->GetStereoVolume(), &volume, ImVec2(35, ImGui::GetWindowHeight() / 1.75f), 140.f + i * 100.f);
		}
		channels.clear();

		ImGui::End();
	}
}