#include "GUI/ContentBrowserGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"

namespace GUI
{
	ContentBrowseGUI::ContentBrowseGUI()
	{
	}

	ContentBrowseGUI::~ContentBrowseGUI()
	{
	}

	void ContentBrowseGUI::Draw()
	{
		ImGuiWindowFlags contentBrowserWindowFlags = ImGuiWindowFlags_None;
		
		ImGui::Begin("Content Browser", 0, contentBrowserWindowFlags);
		ImGui::End();
	}
}