#include "GUI/AudioMixerGUI.hpp"
#include "Core/Scene.hpp"
#include "Core/Audio/AudioSystem.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"

namespace GUI
{
	AudioMixerGUI::AudioMixerGUI() {}

	void AudioMixerGUI::Draw(Core::AudioSystem* _audioSystem)
	{
		ImGui::SetNextWindowSizeConstraints({ 300.f, 350.f }, ImGui::GetMainViewport()->Size);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin("Audio Mixer", 0, ImGuiWindowFlags_HorizontalScrollbar);

		if (!_audioSystem->IsAudioEnabled())
			ImGui::BeginDisabled();

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

		//Play, Pause and Stop buttons
		if (m_playBtnTexture == nullptr)
			m_playBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Start.img");
		if (ImGui::ImageButton("Play", m_playBtnTexture->GetID(), ImVec2(masterChannelSize.x/3.f, masterChannelSize.x / 3.f)))
			_audioSystem->Play();

		ImGui::SameLine();
		if (m_pauseBtnTexture == nullptr)
			m_pauseBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Pause.img");
		if(_audioSystem->IsPaused())
		{
			ImGui::PushStyleColor(ImGuiCol_Border, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.5f, 0.5f, 0.5f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.75f, 0.75f, 0.75f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.85f, 0.85f, 0.85f, 1.f });

			if (ImGui::ImageButton("Unpause", m_pauseBtnTexture->GetID(), ImVec2(masterChannelSize.x / 3.f, masterChannelSize.x / 3.f)))
				_audioSystem->SetPause(false);

			ImGui::PopStyleColor(4);
		}
		else
		{
			if (ImGui::ImageButton("Pause", m_pauseBtnTexture->GetID(), ImVec2(masterChannelSize.x / 3.f, masterChannelSize.x / 3.f)))
				_audioSystem->SetPause(true);
		}

		ImGui::SameLine();
		if (m_stopBtnTexture == nullptr)
			m_stopBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Stop.img");
		if (ImGui::ImageButton("Stop", m_stopBtnTexture->GetID(), ImVec2(masterChannelSize.x / 3.f, masterChannelSize.x / 3.f)))
			_audioSystem->Stop();

		if (!_audioSystem->IsAudioEnabled())
		{
			ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "No audio listener");
			ImGui::EndDisabled();
		}

		ImGui::End();
	}
}