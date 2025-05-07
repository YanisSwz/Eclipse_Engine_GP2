#pragma once
#include "GUI/FolderGUI.hpp"

namespace GUI
{
	class ContentBrowseGUI
	{
	public:
		ContentBrowseGUI() = default;
		~ContentBrowseGUI() = default;

		void Init();
		std::string Draw();
		void Delete();

	private:
		FolderGUI* m_folderRoot = nullptr;
		FolderGUI* m_crtFolderSelected = nullptr;

		bool m_firstFrameHierarchy = true;
	};
}