#pragma once
#include "GUI/FolderGUI.hpp"

namespace GUI
{
	class ContentBrowserGUI
	{
	public:
		ContentBrowserGUI() = default;
		~ContentBrowserGUI() = default;

		void Init();
		std::string Draw();
		void Delete();

		void AddScene(std::string _newScene);

	private:
		FolderGUI* m_folderRoot = nullptr;
		FolderGUI* m_crtFolderSelected = nullptr;

		bool m_firstFrameHierarchy = true;
	};
}