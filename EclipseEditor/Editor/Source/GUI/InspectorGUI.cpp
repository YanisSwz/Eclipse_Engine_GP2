#include "GUI/InspectorGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"
#include "GameObject.hpp"
#include "Model.hpp"

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

		if (!_crtGOselected)
		{
			ImGui::End();
			return;
		}

		DrawTransformComponent(_crtGOselected->transform);
		DrawModelComponent(_crtGOselected->GetComponent<Core::Model>());


		ImGui::End();
	}

	void InspectorGUI::DrawTransformComponent(Core::Transform* _transform)
	{
		if (!_transform)
			return;

		ImGui::SeparatorText("Transform");
		GUI::DragVec3XYZ("Position", _transform->localPosition);
		GUI::DragQuatXYZ("Rotation", _transform->localRotation);
		GUI::DragVec3XYZ("Scale", _transform->localScale, 1.f);
	}

	void InspectorGUI::DrawModelComponent(Core::Model* _model)
	{
		if (!_model)
			return;

		ImGui::SeparatorText("Model");

		std::vector<std::string> textureNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Texture>();
		if (GUI::ComboFilter("Texture: ", &_model->texture->name, textureNames))
			_model->texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(_model->texture->name);

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TextureName"))
			{
				IM_ASSERT(payload->DataSize == sizeof(std::string));
				std::string payload_n;
				payload_n = *static_cast<std::string*>(payload->Data);
				_model->texture->name = payload_n.c_str();
				_model->texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(payload_n);
			}
			ImGui::EndDragDropTarget();
		}
	}
}