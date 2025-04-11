#include "GUI/ConsoleGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"

namespace GUI
{
	ConsoleGUI::ConsoleGUI()
	{
	}

	ConsoleGUI::~ConsoleGUI()
	{
	}

	void ConsoleGUI::Draw()
	{
		ImGuiWindowFlags consoleWindowFlags = ImGuiWindowFlags_None;

		ImGui::Begin("Console", 0, consoleWindowFlags);
		ImGui::End();
	}
}