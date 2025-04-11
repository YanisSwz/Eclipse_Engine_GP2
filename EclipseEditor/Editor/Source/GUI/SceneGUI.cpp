#include "GUI/SceneGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"

namespace GUI
{
	SceneGUI::SceneGUI()
	{
	}

	SceneGUI::~SceneGUI()
	{
	}

	void SceneGUI::Draw(const unsigned int _textureID, int& _windowWidth, int& _windowHeight, int& _windowPosX, int& _windowPosY)
	{
		ImGuiWindowFlags sceneWindowFlags = ImGuiWindowFlags_None;

		ImGui::Begin("Scene", 0, sceneWindowFlags);
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 windowPos = ImGui::GetWindowPos();
		_windowWidth = static_cast<int>(windowSize.x);
		_windowHeight = static_cast<int>(windowSize.y);
		_windowPosX = static_cast<int>(windowPos.x);
		_windowPosY = static_cast<int>(windowPos.y);

		ImGui::GetWindowDrawList()->AddImage(
			static_cast<intptr_t>(_textureID),
			ImVec2(windowPos.x, windowPos.y),
			ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
			ImVec2(0, 1),
			ImVec2(1, 0));

		ImGui::End();
	}
}