#include "GUI/GameGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"

namespace GUI
{
	void GameGUI::Draw()
	{
		ImGui::SetNextWindowSizeConstraints({ 300.f, 300.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags sceneWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Game", 0, sceneWindowFlags);
		ImGui::End();
	}
}