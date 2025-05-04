#include "GUI/FolderGUI.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"
#include "Resource/Mesh.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include <math.h>

namespace GUI
{
	Resource::Texture* FolderGUI::m_folderIcon = nullptr;
	Resource::Texture* FolderGUI::m_meshIcon = nullptr;

	FolderGUI::FolderGUI(std::string _name)
		: name(_name)
	{

	}

	void FolderGUI::Init()
	{
		if (name == "Texture")
		{
			std::vector<std::string> textureNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Texture>();
			for (std::string textureName : textureNames)
				m_textureFiles.push_back(Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(textureName));

			return;
		}
		if (name == "Mesh")
		{
			std::vector<std::string> meshNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Mesh>();
			for (std::string meshName : meshNames)
				m_meshFiles.push_back(Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(meshName));

			return;
		}

		m_folderIcon = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("FolderIcon.img");
		m_meshIcon = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("MeshIcon.img");

		FolderGUI* textureFolder = new FolderGUI("Texture");
		m_folderChildren.push_back(textureFolder);
		textureFolder->Init();
		textureFolder->SetParent(this);

		FolderGUI* meshFolder = new FolderGUI("Mesh");
		m_folderChildren.push_back(meshFolder);
		meshFolder->Init();
		meshFolder->SetParent(this);
	}

	void FolderGUI::SetParent(FolderGUI* _parent)
	{
		m_parent = _parent;
	}

	FolderGUI* FolderGUI::DrawHierarchy(const FolderGUI& _currentFolder)
	{
		FolderGUI* newFolderSelected = nullptr;

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_LabelSpanAllColumns | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
		if (this == &_currentFolder)
			treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

		if (ImGui::TreeNodeEx(name.c_str(), treeNodeFlags))
		{
			if (ImGui::IsItemClicked())
				newFolderSelected = this;

			for (FolderGUI* child : m_folderChildren)
			{
				FolderGUI* tempFolderSelected = child->DrawHierarchy(_currentFolder);
				if (tempFolderSelected)
					newFolderSelected = tempFolderSelected;
			}
			ImGui::TreePop();
		}

		return newFolderSelected;
	}

	FolderGUI* FolderGUI::Draw()
	{
		if (m_parent)
		{
			if (ImGui::Button("Return"))
				return m_parent;
		}
		FolderGUI* newCrtFolder = nullptr;

		int folderChildrenSize = static_cast<int>(m_folderChildren.size());
		int texturesFilesSize = static_cast<int>(m_textureFiles.size());
		int meshFilesSize = static_cast<int>(m_meshFiles.size());

		int nbElem = folderChildrenSize + texturesFilesSize + meshFilesSize;
		float tempNbElemInColumn = ImGui::GetColumnWidth() / 150.f;
		int nbElemInColumn = fmod(tempNbElemInColumn, 1.f) <= 0.65f ? static_cast<int>(tempNbElemInColumn) - 2 : static_cast<int>(tempNbElemInColumn) - 1;

		if (nbElemInColumn == 0)
			nbElemInColumn = 1;

		if (nbElemInColumn > 0)
		{
			if (ImGui::BeginTable("Content Browser Table", nbElemInColumn, ImGuiTableFlags_SizingFixedSame | ImGuiTableFlags_NoBordersInBody))
			{
				for (int i = 0; i < nbElem; ++i)
				{
					if (i % nbElemInColumn == 0)
						ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(i % nbElemInColumn);
					ImGui::SetNextItemWidth(150.f);

					if (i < folderChildrenSize)
					{
						FolderGUI* tempNewCrtFolder = DrawFolderGUI(i);
						if (tempNewCrtFolder)
							newCrtFolder = tempNewCrtFolder;
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
		return newCrtFolder;
	}

	FolderGUI* FolderGUI::DrawFolderGUI(int _index)
	{
		FolderGUI* newFolderSelected = nullptr;

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));
		
		std::string invisibleFolderName = "##";
		invisibleFolderName.append(m_folderChildren[_index]->name).append(" Folder Button");
		if (ImGui::ImageButton(invisibleFolderName.c_str(), m_folderIcon->GetID(), { 100.f, 100.f }, { 0.f, 1.f }, { 1.f, 0.f }))
			newFolderSelected = m_folderChildren[_index];
		
		ImGui::PopStyleVar();
		ImGui::Text(m_folderChildren[_index]->name.c_str());
		return newFolderSelected;
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