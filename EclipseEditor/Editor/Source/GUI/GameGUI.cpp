#include "GUI/GameGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Camera/Camera.hpp"

namespace GUI
{
	void GameGUI::Draw(Core::Camera* _currentCam, const unsigned int _textureID, int& _windowWidth, int& _windowHeight)
	{
		ImGui::SetNextWindowSizeConstraints({ 300.f, 300.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags sceneWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Game", 0, sceneWindowFlags);

		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 windowPos = ImGui::GetWindowPos();

		if (!_currentCam)
		{
			ImGui::SetCursorPos({ windowSize.x / 2.f - 80.f, windowSize.y / 2.f });
			ImGui::SetWindowFontScale(2.f);
			ImGui::Text("No Camera");
			ImGui::SetWindowFontScale(1.f);

			ImGui::End();
			return;
		}

		_windowWidth = static_cast<int>(windowSize.x);
		_windowHeight = static_cast<int>(windowSize.y);
		ImVec2 uv0{ 0.f, 1.f };
		ImVec2 uv1{ 1.f, 0.f };

		ImGui::GetWindowDrawList()->AddImage(
			static_cast<intptr_t>(_textureID),
			ImVec2(windowPos.x, windowPos.y),
			ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
			uv0, uv1);

		ImGui::End();
	}
}