#include "GUI/InspectorGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "GameObject.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"

namespace GUI
{
	InspectorGUI::InspectorGUI()
	{
	}

	InspectorGUI::~InspectorGUI()
	{
	}

	void InspectorGUI::Draw(Core::GameObject* _crtGOselected)
	{
		ImGuiWindowFlags inspectorWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Inspector", 0, inspectorWindowFlags);

		ImGui::SeparatorText("Transform");
		if (_crtGOselected)
		{
			GUI::DragVec3XYZ("Position", _crtGOselected->transform->localPosition);
			GUI::DragQuatXYZ("Rotation", _crtGOselected->transform->localRotation);
			GUI::DragVec3XYZ("Scale", _crtGOselected->transform->localScale, 1.f);
		}

		ImGui::SeparatorText("Model");
		static std::vector<std::string> textureNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Texture>();
		static std::string crtTexture = "";

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.f);
		ImGui::Text("Texture: ");
		ImGui::NextColumn();
		static ImGuiComboFlags comboFlags = 0;
		if (ImGui::BeginCombo("##Texture Combo (w/ filter)", crtTexture.c_str(), comboFlags))
		{
			static ImGuiTextFilter filter;
			if (ImGui::IsWindowAppearing())
			{
				ImGui::SetKeyboardFocusHere();
				filter.Clear();
			}
			ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
			filter.Draw("##Filter", -FLT_MIN);

			for (int i = 0; i < textureNames.size(); ++i)
			{
				const bool is_selected = (crtTexture == textureNames[i]);
				if (filter.PassFilter(textureNames[i].c_str()))
					if (ImGui::Selectable(textureNames[i].c_str(), is_selected))
						crtTexture = textureNames[i];
			}
			ImGui::EndCombo();
		}

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TextureName"))
			{
				IM_ASSERT(payload->DataSize == sizeof(std::string));
				std::string payload_n;
				payload_n = *static_cast<std::string*>(payload->Data);
				crtTexture = payload_n;
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::End();
	}
}