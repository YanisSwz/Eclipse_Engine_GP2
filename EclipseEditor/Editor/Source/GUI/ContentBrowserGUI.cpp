#include "GUI/ContentBrowserGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"

namespace GUI
{
	void ContentBrowserGUI::Init()
	{
		m_folderRoot = new FolderGUI("Assets");
		m_folderRoot->Init();
		m_crtFolderSelected = m_folderRoot;
	}

	std::string ContentBrowserGUI::Draw()
	{
		std::string selectedScene;

		ImGui::SetNextWindowSizeConstraints({ 100.f, 200.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags contentBrowserWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Content Browser", 0, contentBrowserWindowFlags);

		ImGui::Columns(2);
		if (m_firstFrameHierarchy)
		{
			m_firstFrameHierarchy = false;
			ImGui::SetColumnWidth(0, ImGui::GetContentRegionAvail().x / 3.f);
		}

		FolderGUI* tempNewFolderSelected = m_folderRoot->DrawHierarchy(*m_crtFolderSelected);
		if (tempNewFolderSelected)
			m_crtFolderSelected = tempNewFolderSelected;

		ImGui::NextColumn();

		tempNewFolderSelected = m_crtFolderSelected->Draw(selectedScene);
		if (tempNewFolderSelected)
			m_crtFolderSelected = tempNewFolderSelected;

		ImGui::Columns(1);

		ImGui::End();

		return selectedScene;
	}

	void ContentBrowserGUI::Delete()
	{
		m_folderRoot->Delete();
	}

	void ContentBrowserGUI::AddScene(std::string _newScene)
	{
		std::vector<FolderGUI*> folders = m_folderRoot->GetChildren();
		for (int i = 0; i < folders.size(); ++i)
		{
			if (folders[i]->name == "Scene")
				folders[i]->AddSceneFile(_newScene);
		}
	}
}