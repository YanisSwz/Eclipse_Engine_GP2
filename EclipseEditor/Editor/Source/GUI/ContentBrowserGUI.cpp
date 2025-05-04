#include "GUI/ContentBrowserGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"

namespace GUI
{
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

		ImGui::Columns(2);
		static bool first = true;
		if (first)
		{
			first = false;
			ImGui::SetColumnWidth(0, ImGui::GetContentRegionAvail().x / 3.f);
		}

		FolderGUI* tempNewFolderSelected = m_folderRoot->DrawHierarchy(*m_crtFolderSelected);
		if (tempNewFolderSelected)
			m_crtFolderSelected = tempNewFolderSelected;

		ImGui::NextColumn();

		tempNewFolderSelected = m_crtFolderSelected->Draw();
		if (tempNewFolderSelected)
			m_crtFolderSelected = tempNewFolderSelected;

		ImGui::Columns(1);

		ImGui::End();
	}

	void ContentBrowseGUI::Delete()
	{
		m_folderRoot->Delete();
	}
}