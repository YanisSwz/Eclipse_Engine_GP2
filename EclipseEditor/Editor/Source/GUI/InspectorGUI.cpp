#include "GUI/InspectorGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"
#include "Core/Physics/BoxCollider.hpp"
#include "Core/Physics/CapsuleCollider.hpp"
#include "Core/Physics/MeshCollider.hpp"
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
		ImGui::SetNextWindowSizeConstraints({400.f, 50.f}, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags inspectorWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Inspector", 0, inspectorWindowFlags);

		if (!_crtGOselected)
		{
			ImGui::End();
			return;
		}
		if (ImGui::InputText("##Name", _crtGOselected->name.data(), 255))
		{
			_crtGOselected->name = _crtGOselected->name.c_str();
			if (_crtGOselected->name.size() == 0)
				_crtGOselected->name = "GameObject" + std::to_string(_crtGOselected->GetID());
		}
		DrawTransformComponent(_crtGOselected->transform);
		DrawModelComponent(_crtGOselected->GetComponent<Core::Model>());
		DrawBoxColliderComponent(_crtGOselected->GetComponent<Core::BoxCollider>());
		DrawCapsuleColliderComponent(_crtGOselected->GetComponent<Core::CapsuleCollider>());
		DrawMeshColliderComponent(_crtGOselected->GetComponent<Core::MeshCollider>());

		ImGui::End();
	}

	void InspectorGUI::DrawTransformComponent(Core::Transform* _transform)
	{
		if (!_transform)
			return;

		ImGui::SeparatorText("Transform");
		if (GUI::DragVec3XYZ("Position", _transform->GetLocalPositionRef()))
			_transform->SetPositionChanged();
		if (GUI::DragVec3XYZ("Rotation", _transform->GetLocalEulerAnglesRef()))
			_transform->SetRotationChanged();
		if (GUI::DragVec3XYZ("Scale", _transform->GetLocalScaleRef(), 1.f))
			_transform->SetScaleChanged();
	}

	void InspectorGUI::DrawModelComponent(Core::Model* _model)
	{
		if (!_model)
			return;

		ImGui::NewLine();
		ImGui::SeparatorText("Model");

		std::vector<std::string> meshNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Mesh>();
		std::string meshName = _model->mesh->name;
		if (GUI::ComboFilter("Mesh ", &meshName, meshNames))
			_model->mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(meshName);
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MeshName"))
			{
				IM_ASSERT(payload->DataSize == sizeof(std::string));
				std::string payload_n;
				payload_n = *static_cast<std::string*>(payload->Data);
				_model->mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(payload_n);
			}
			ImGui::EndDragDropTarget();
		}

		ImGui::Columns(1);

		std::vector<std::string> textureNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Texture>();
		std::string textureName = _model->texture->name;
		if (GUI::ComboFilter("Texture ", &textureName, textureNames))
			_model->texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(textureName);
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TextureName"))
			{
				IM_ASSERT(payload->DataSize == sizeof(std::string));
				std::string payload_n;
				payload_n = *static_cast<std::string*>(payload->Data);
				_model->texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(payload_n);
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::Columns(1);
	}

	void InspectorGUI::DrawBoxColliderComponent(Core::BoxCollider* _collider)
	{
		if (!_collider)
			return;
		ImGui::NewLine();
		ImGui::SeparatorText("Box Collider");

		bool isDynamic = _collider->GetIsDynamic();
		if (GUI::CheckBox("Is Dynamic ", "BoxColliderIsDynamic", &isDynamic))
			_collider->SetDynamic(isDynamic);

		float mass = _collider->GetMass();
		if (GUI::DragFloat("Mass ", "BoxColliderMass", &mass, 0.1f, 0.1f, 1000.f, "%.3f Kg"))
		{
			if (mass > 0.f)
				_collider->SetMass(mass);
		}

		Math::Vec3 posOffset = _collider->GetOffsetPos();
		if (GUI::DragVec3XYZ("Offset", posOffset))
			_collider->SetOffsetPos(posOffset);

		Math::Vec3 scale = _collider->GetScale();
		if (GUI::DragVec3XYZ("Size", scale, 1.f))
			_collider->Scale(scale);
	}

	void InspectorGUI::DrawCapsuleColliderComponent(Core::CapsuleCollider* _collider)
	{
		if (!_collider)
			return;
		ImGui::NewLine();
		ImGui::SeparatorText("Capsule Collider");

		bool isDynamic = _collider->GetIsDynamic();
		if (GUI::CheckBox("Is Dynamic ", "CapsuleColliderIsDynamic", &isDynamic))
			_collider->SetDynamic(isDynamic);

		float mass = _collider->GetMass();
		if (GUI::DragFloat("Mass ", "CapsuleColliderMass", &mass, 0.1f, 0.1f, 1000.f, "%.3f Kg"))
		{
			if (mass > 0.f)
				_collider->SetMass(mass);
		}

		Math::Vec3 posOffset = _collider->GetOffsetPos();
		if (GUI::DragVec3XYZ("Offset", posOffset))
			_collider->SetOffsetPos(posOffset);

		Math::Vec3 scale = _collider->GetScale();
		if (GUI::DragFloat("Height", "BoxColliderHeight", &scale.y, 0.1f, 0.f, 100.f, "%.3f m"))
			_collider->Scale(scale);
		
		if (GUI::DragFloat("Radius", "BoxColliderRadius", &scale.x, 0.1f, 0.f, 100.f, "%.3f m"))
		{
			scale.z = scale.x;
			_collider->Scale(scale);
		}
	}

	void InspectorGUI::DrawMeshColliderComponent(Core::MeshCollider* _collider)
	{
		if (!_collider)
			return;
		ImGui::NewLine();
		ImGui::SeparatorText("Mesh Collider");

		bool isDynamic = _collider->GetIsDynamic();
		if (GUI::CheckBox("Is Dynamic ", "MeshColliderIsDynamic", &isDynamic))
			_collider->SetDynamic(isDynamic);

		float mass = _collider->GetMass();
		if (GUI::DragFloat("Mass ", "MeshColliderMass", &mass, 0.1f, 0.1f, 1000.f, "%.3f Kg"))
		{
			if (mass > 0.f)
				_collider->SetMass(mass);
		}

		Math::Vec3 posOffset = _collider->GetOffsetPos();
		if (GUI::DragVec3XYZ("Offset", posOffset))
			_collider->SetOffsetPos(posOffset);

		Math::Vec3 scale = _collider->GetScale();
		if (GUI::DragVec3XYZ("Size", scale, 1.f))
			_collider->Scale(scale);
	}
}