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
		ImGui::SetNextWindowSizeConstraints({ 300.f, 100.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags consoleWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Console", 0, consoleWindowFlags);

		ImGui::SetWindowFontScale(1.25f);

		std::string filePath = Logging::Logger::GetInstance().GetFilePath();
		
		if (filePath != "")
		{
			std::ifstream file;
			file.open(filePath);
			while (file.good())
			{
				std::string str;
				getline(file, str);
				Logging::COLOR color = Logging::COLOR::WHITE;
				if (str.find("[INFO]") != std::string::npos)
					color = Logging::COLOR::GREEN;
				else if (str.find("[WARNING]") != std::string::npos)
					color = Logging::COLOR::YELLOW;
				else if (str.find("[ERROR]") != std::string::npos)
					color = Logging::COLOR::RED;
				ColoredText(str.c_str(), color);
			}
			file.close();
		}

		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.f);

		ImGui::End();
	}
}