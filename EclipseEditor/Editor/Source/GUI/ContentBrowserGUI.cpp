#include "GUI/ContentBrowserGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/Texture.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Resource/Skybox.hpp"

namespace GUI
{
	ContentBrowseGUI::ContentBrowseGUI()
	{
	}

	ContentBrowseGUI::~ContentBrowseGUI()
	{
	}

	void ContentBrowseGUI::Draw()
	{
		static std::vector<std::string> textureNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Texture>();

		ImGuiWindowFlags contentBrowserWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Content Browser", 0, contentBrowserWindowFlags);

		Resource::Texture* texture;
		int nbElem = static_cast<int>(textureNames.size());
		int nbElemInCollumn = static_cast<int>(ImGui::GetContentRegionAvail().x / 100.f) - 1;
		if (nbElemInCollumn > 0)
		{
			if (ImGui::BeginTable("Content Browser Table", nbElemInCollumn, ImGuiTableFlags_NoBordersInBody))
			{
				for (int i = 0; i < nbElem; ++i)
				{
					if (i % nbElemInCollumn == 0)
						ImGui::TableNextRow();

					ImGui::PushID(i);
					ImGui::TableSetColumnIndex(i % nbElemInCollumn);
					texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(textureNames[i]);
					DrawImage(textureNames[i].c_str(), texture->GetID(), 100.f);

					if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
					{
						ImGui::SetDragDropPayload("TextureName", &textureNames[i], sizeof(std::string));
						DrawImage(textureNames[i].c_str(), texture->GetID(), 100.f);
						ImGui::Text(textureNames[i].c_str());
						ImGui::EndDragDropSource();
					}
					ImGui::PopID();


					ImGui::Text(textureNames[i].c_str());
				}
				ImGui::EndTable();
			}
		}



		ImGui::End();
	}
}