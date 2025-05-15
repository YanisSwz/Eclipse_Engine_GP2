#pragma once
#include "GUI/FolderGUI.hpp"

namespace Core
{
	class GameObject;
}

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
		void AddPrefab(Resource::Prefab* _newPrefab);

	private:
		FolderGUI* m_folderRoot = nullptr;
		FolderGUI* m_crtFolderSelected = nullptr;

		bool m_firstFrameHierarchy = true;
	};
}