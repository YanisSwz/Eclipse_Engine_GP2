#pragma once
#include <vector>
#include <string>

namespace Resource
{
	class Texture;
	class Mesh;
	class AudioClip;
}

namespace GUI
{
	class FolderGUI
	{
	public:
		FolderGUI(std::string _name = "");
		~FolderGUI() = default;

		std::string name;

		static void InitIcons();
		void Init();
		void SetParent(FolderGUI* _parent);

		FolderGUI* DrawHierarchy(const FolderGUI& _currentFolder);

		FolderGUI* Draw(std::string& _selectedScene);
		FolderGUI* DrawFolderGUI(int _index);
		void DrawTextureGUI(int _index);
		void DrawMeshGUI(int _index);
		void DrawAudioGUI(int _index);
		void DrawSceneGUI(int _index, std::string& _selectedScene);
		void Delete();

		void AddSceneFile(std::string _newSceneFile);
		inline std::vector<FolderGUI*> GetChildren() { return m_folderChildren; }

	private:
		FolderGUI* m_parent = nullptr;
		std::vector<FolderGUI*> m_folderChildren;
		std::vector<Resource::Texture*> m_textureFiles;
		std::vector<Resource::Mesh*> m_meshFiles;
		std::vector<Resource::AudioClip*> m_audioFiles;
		std::vector<std::string> m_sceneFiles;

		static Resource::Texture* m_folderIcon;
		static Resource::Texture* m_meshIcon;
		static Resource::Texture* m_audioIcon;
		static Resource::Texture* m_sceneIcon;
	};
}