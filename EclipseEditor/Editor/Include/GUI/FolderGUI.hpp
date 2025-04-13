#pragma once
#include <vector>
#include <string>

namespace Resource
{
	class Texture;
}

namespace GUI
{
	class FolderGUI
	{
	public:
		FolderGUI(std::string _name = "");
		~FolderGUI();

		std::string name;

		void Init();
		FolderGUI* Draw();
		FolderGUI* DrawFolderGUI(int _index);
		void DrawTextureGUI(int _index);
		void Delete();

	private:
		std::vector<FolderGUI*> m_folderChildren;
		std::vector<Resource::Texture*> m_textureFiles;

		static Resource::Texture* m_folderIcon;
	};
}