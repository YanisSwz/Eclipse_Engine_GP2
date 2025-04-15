#include "GUI/ConsoleGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Logger.hpp"
#include <string>
#include <fstream>

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

		std::string filePath = Logging::Logger::Get()->GetFilePath();
		
		if (filePath != "")
		{
			std::ifstream file;
			file.open(filePath);
			while (file.good())
			{
				std::string str;
				getline(file, str);
				ImGui::Text(str.c_str());
			}
			file.close();
		}

		ImGui::End();
	}
}