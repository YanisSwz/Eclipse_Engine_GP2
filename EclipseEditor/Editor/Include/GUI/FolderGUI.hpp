#pragma once
#include <vector>
#include <string>

namespace Resource
{
	class Texture;
	class Mesh;
}

namespace GUI
{
	class FolderGUI
	{
	public:
		FolderGUI(std::string _name = "");
		~FolderGUI() = default;

		std::string name;

		void Init();
		void SetParent(FolderGUI* _parent);

		FolderGUI* DrawHierarchy(const FolderGUI& _currentFolder);

		FolderGUI* Draw();
		FolderGUI* DrawFolderGUI(int _index);
		void DrawTextureGUI(int _index);
		void DrawMeshGUI(int _index);
		void Delete();

	private:
		FolderGUI* m_parent = nullptr;
		std::vector<FolderGUI*> m_folderChildren;
		std::vector<Resource::Texture*> m_textureFiles;
		std::vector<Resource::Mesh*> m_meshFiles;

		static Resource::Texture* m_folderIcon;
		static Resource::Texture* m_meshIcon;
	};
}