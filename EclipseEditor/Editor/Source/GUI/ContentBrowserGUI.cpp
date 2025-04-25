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

	void ContentBrowseGUI::Init()
	{
		m_folderRoot = new FolderGUI("Root");
		m_folderRoot->Init();
		m_crtFolderSelected = m_folderRoot;
	}

	void ContentBrowseGUI::Draw()
	{
		ImGui::SetNextWindowSizeConstraints({ 100.f, 200.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags contentBrowserWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Content Browser", 0, contentBrowserWindowFlags);

		FolderGUI* newFolderSelected = m_crtFolderSelected->Draw();
		if (newFolderSelected)
			m_crtFolderSelected = newFolderSelected;

		ImGui::End();
	}

	void ContentBrowseGUI::Delete()
	{
		m_folderRoot->Delete();
	}
}