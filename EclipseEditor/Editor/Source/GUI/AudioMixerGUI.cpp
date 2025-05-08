#include "GUI/AudioMixerGUI.hpp"
#include "Core/Scene.hpp"
#include "Core/Audio/AudioSystem.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"

namespace GUI
{
	AudioMixerGUI::AudioMixerGUI() {}

	void AudioMixerGUI::Draw(Core::AudioSystem* _audioSystem)
	{
		ImGui::SetNextWindowSizeConstraints({ 300.f, 350.f }, ImGui::GetMainViewport()->Size);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin("Audio Mixer", 0, ImGuiWindowFlags_HorizontalScrollbar);

		// Master volume
		ImVec2 masterChannelSize{ 50.f, ImGui::GetWindowHeight() / 1.5f };
		float volume = _audioSystem->GetMaxVolume();
		if (GUI::AudioChannel("Master", _audioSystem->GetStereoVolume(), volume, masterChannelSize))
			_audioSystem->SetMaxVolume(volume);

		// Audio sources
		ImVec2 audioSourcesChannelSize{ 35.f, ImGui::GetWindowHeight() / 1.75f };
		float offset = 140.f;
		std::vector<Core::AudioSource*> channels = _audioSystem->GetAudioSources();
		if (!channels.empty())
		{
			for (int i = 0; i < channels.size(); ++i)
			{
				ImGui::SameLine();
				if (!channels[i]->IsActive() || channels[i]->GetClip() == nullptr)
					ImGui::BeginDisabled();
				float vol = channels[i]->GetMaxVolume();
				if (!channels[i]->Is3D())
				{
					float pan = channels[i]->GetPan();
					if (GUI::AudioChannel(channels[i]->GetGameObject()->name.c_str(), channels[i]->IsPlaying(), &pan, vol, audioSourcesChannelSize, offset + i * offset, i))
					{
						channels[i]->SetPan(pan);
						channels[i]->SetMaxVolume(vol);
					}
				}
				else
				{
					if (GUI::AudioChannel3D(channels[i]->GetGameObject()->name.c_str(), channels[i]->IsPlaying(), vol, audioSourcesChannelSize, offset + i * offset, i))
						channels[i]->SetMaxVolume(vol);
				}
				if (!channels[i]->IsActive() || channels[i]->GetClip() == nullptr)
					ImGui::EndDisabled();
			}
			channels.clear();
		}

		
		if (ImGui::Button("Play", ImVec2(masterChannelSize.x, 40.f)))
			_audioSystem->Play();

		if(_audioSystem->IsPaused())
		{
			if (ImGui::Button("Unpause", ImVec2(masterChannelSize.x, 40.f)))
				_audioSystem->SetPause(false);
		}
		else
		{
			if (ImGui::Button("Pause", ImVec2(masterChannelSize.x, 40.f)))
				_audioSystem->SetPause(true);
		}

		if (ImGui::Button("Stop", ImVec2(masterChannelSize.x, 40.f)))
			_audioSystem->Stop();

		ImGui::End();
	}
}