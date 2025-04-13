#include "GUI/FolderGUI.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"
#include "Resource/Mesh.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"

namespace GUI
{
	Resource::Texture* FolderGUI::m_folderIcon = nullptr;
	Resource::Texture* FolderGUI::m_meshIcon = nullptr;

	FolderGUI::FolderGUI(std::string _name)
		: name(_name)
	{

	}

	FolderGUI::~FolderGUI()
	{

	}

	void FolderGUI::Init()
	{
		if (name == "Texture")
		{
			std::vector<std::string> textureNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Texture>();
			for (std::string textureName : textureNames)
				m_textureFiles.push_back(Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(textureName));

			std::vector<std::string> meshNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Mesh>();
			for (std::string meshName : meshNames)
				m_meshFiles.push_back(Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(meshName));

			FolderGUI* textureFolder = new FolderGUI("Editor");
			m_folderChildren.push_back(textureFolder);

			return;
		}

		m_folderIcon = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("FolderIcon.img");
		m_meshIcon = m_folderIcon;
		FolderGUI* textureFolder = new FolderGUI("Texture");
		m_folderChildren.push_back(textureFolder);
		textureFolder->Init();
	}

	FolderGUI* FolderGUI::Draw()
	{

		int folderChildrenSize = static_cast<int>(m_folderChildren.size());
		int texturesFilesSize = static_cast<int>(m_textureFiles.size());
		int meshFilesSize = static_cast<int>(m_meshFiles.size());

		int nbElem = folderChildrenSize + texturesFilesSize + meshFilesSize;
		int nbElemInCollumn = static_cast<int>(ImGui::GetContentRegionAvail().x / 100.f) - 1;
		if (nbElemInCollumn > 0)
		{
			if (ImGui::BeginTable("Content Browser Table", nbElemInCollumn, ImGuiTableFlags_NoBordersInBody))
			{
				for (int i = 0; i < nbElem; ++i)
				{
					if (i % nbElemInCollumn == 0)
						ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(i % nbElemInCollumn);

					if (i < folderChildrenSize)
					{
						FolderGUI* newCrtFolder = DrawFolderGUI(i);
						if (newCrtFolder)
							return newCrtFolder;
					}
					else if (i < folderChildrenSize + texturesFilesSize)
					{
						DrawTextureGUI(i);
					}
					else if (i < folderChildrenSize + texturesFilesSize + meshFilesSize)
					{
						DrawMeshGUI(i);
					}
				}
				ImGui::EndTable();
			}
		}
		return nullptr;
	}

	FolderGUI* FolderGUI::DrawFolderGUI(int _index)
	{
		std::string invisibleFolderName = "##";

		invisibleFolderName.append(name).append(" Folder Button");
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
		if (ImGui::ImageButton(invisibleFolderName.c_str(), m_folderIcon->GetID(), { 100.f, 100.f }))
		{
			ImGui::PopStyleVar();
			ImGui::EndTable();
			return m_folderChildren[_index];
		}
		ImGui::PopStyleVar();
		ImGui::Text(m_folderChildren[_index]->name.c_str());
		return nullptr;
	}

	void FolderGUI::DrawTextureGUI(int _index)
	{
		ImGui::PushID(_index);
		Resource::Texture* texture = m_textureFiles[_index - m_folderChildren.size()];
		DrawImage(texture->name.c_str(), texture->GetID(), 100.f);

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("TextureName", &texture->name, sizeof(std::string));
			DrawImage(texture->name.c_str(), texture->GetID(), 100.f);
			ImGui::Text(texture->name.c_str());
			ImGui::EndDragDropSource();
		}
		ImGui::Text(texture->name.c_str());
		ImGui::PopID();
	}

	void FolderGUI::DrawMeshGUI(int _index)
	{
		ImGui::PushID(_index);
		Resource::Mesh* mesh = m_meshFiles[_index - m_folderChildren.size() - m_textureFiles.size()];
		DrawImage(mesh->name.c_str(), m_meshIcon->GetID(), 100.f);

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("MeshName", &mesh->name, sizeof(std::string));
			DrawImage(mesh->name.c_str(), m_meshIcon->GetID(), 100.f);
			ImGui::Text(mesh->name.c_str());
			ImGui::EndDragDropSource();
		}
		ImGui::Text(mesh->name.c_str());
		ImGui::PopID();
	}

	void FolderGUI::Delete()
	{
		for (FolderGUI* folder : m_folderChildren)
			folder->Delete();
		delete this;
	}
}