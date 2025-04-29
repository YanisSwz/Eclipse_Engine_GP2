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
		//ImGui::Begin("            Content Browser", 0, contentBrowserWindowFlags);
		//ImVec2 windowPos = ImGui::GetWindowPos();
		//ImVec2 windowSize = ImGui::GetWindowSize();
		//Resource::Texture* folderIcon = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("FolderIcon.img");

		//ImGui::PushClipRect(windowPos, windowSize, false);
		//ImGui::SetCursorPos(ImVec2(35.f, 0.f));
		//ImGui::Image(folderIcon->GetID(), { 30.f, 30.f }, {0, 1}, {1, 0});
		//ImGui::PopClipRect(); 

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