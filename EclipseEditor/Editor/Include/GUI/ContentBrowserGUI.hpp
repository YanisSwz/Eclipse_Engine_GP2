#pragma once
#include "GUI/FolderGUI.hpp"

namespace GUI
{
	class ContentBrowseGUI
	{
	public:
		ContentBrowseGUI();
		~ContentBrowseGUI();

		void Init();
		void Draw();
		void Delete();

	private:
		FolderGUI* m_folderRoot = nullptr;
		FolderGUI* m_crtFolderSelected = nullptr;
	};
}