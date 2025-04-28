#include "GUI/InspectorGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"
#include "Core/Physics/BoxCollider.hpp"
#include "Core/Physics/CapsuleCollider.hpp"
#include "Core/Physics/MeshCollider.hpp"
#include "Core/Lighting/DirectionalLight.hpp"
#include "Core/Lighting/PointLight.hpp"
#include "Core/Lighting/SpotLight.hpp"
#include "GameObject.hpp"
#include "Model.hpp"

namespace GUI
{
	InspectorGUI::InspectorGUI()
	{
		m_treeNodeComponentFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed;
		m_treeNodeAddComponentFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;
		m_PopupAddComponentFlags = ImGuiPopupFlags_MouseButtonMiddle;
		m_alreadyAddComponentWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	}

	void InspectorGUI::Draw(Core::GameObject* _crtGOSelected)
	{
		ImGui::SetNextWindowSizeConstraints({ 400.f, 50.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags inspectorWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Inspector", 0, inspectorWindowFlags);

		if (!_crtGOSelected)
		{
			ImGui::End();
			return;
		}
		if (ImGui::InputText("##Name", _crtGOSelected->name.data(), 255))
		{
			_crtGOSelected->name = _crtGOSelected->name.c_str();
			if (_crtGOSelected->name.size() == 0)
				_crtGOSelected->name = "GameObject" + std::to_string(_crtGOSelected->GetID());
		}
		ImGui::NewLine();

		DrawTransformComponent(_crtGOSelected->transform);
		DrawModelComponent(_crtGOSelected->GetComponent<Core::Model>());
		DrawBoxColliderComponent(_crtGOSelected->GetComponent<Core::BoxCollider>());
		DrawCapsuleColliderComponent(_crtGOSelected->GetComponent<Core::CapsuleCollider>());
		DrawMeshColliderComponent(_crtGOSelected->GetComponent<Core::MeshCollider>());
		DrawDirectionalLightComponent(_crtGOSelected->GetComponent<Core::DirectionalLight>());
		DrawPointLightComponent(_crtGOSelected->GetComponent<Core::PointLight>());
		DrawSpotLightComponent(_crtGOSelected->GetComponent<Core::SpotLight>());

		DrawAddComponent(_crtGOSelected);
		ImGui::End();
	}

	void InspectorGUI::DrawDeleteComponentPopup(Core::Component* _component)
	{
		if (ImGui::BeginPopupContextItem("DeleteComponent"))
		{
			if (ImGui::Button("Delete"))
				_component->Remove();
			ImGui::EndPopup();
		}
	}

	void InspectorGUI::DrawTransformComponent(Core::Transform* _transform)
	{
		if (!_transform)
			return;

		if (ImGui::TreeNodeEx("Transform", m_treeNodeComponentFlags))
		{
			if (GUI::DragVec3XYZ("Position", _transform->GetLocalPositionRef()))
				_transform->SetPositionChanged();
			if (GUI::DragVec3XYZ("Rotation", _transform->GetLocalEulerAnglesRef()))
				_transform->SetRotationChanged();
			if (GUI::DragVec3XYZ("Scale", _transform->GetLocalScaleRef(), 1.f))
				_transform->SetScaleChanged();

			ImGui::TreePop();
			ImGui::NewLine();
		}
	}

	void InspectorGUI::DrawModelComponent(Core::Model* _model)
	{
		if (!_model)
			return;

		if (ImGui::TreeNodeEx("Model", m_treeNodeComponentFlags))
		{
			DrawDeleteComponentPopup(_model);

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
			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawBoxColliderComponent(Core::BoxCollider* _collider)
	{
		if (!_collider)
			return;

		if (ImGui::TreeNodeEx("Box Collider", m_treeNodeComponentFlags))
		{
			DrawDeleteComponentPopup(_collider);

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

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawCapsuleColliderComponent(Core::CapsuleCollider* _collider)
	{
		if (!_collider)
			return;

		if (ImGui::TreeNodeEx("Capsule Collider", m_treeNodeComponentFlags))
		{
			DrawDeleteComponentPopup(_collider);

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

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawMeshColliderComponent(Core::MeshCollider* _collider)
	{
		if (!_collider)
			return;

		if (ImGui::TreeNodeEx("Mesh Collider", m_treeNodeComponentFlags))
		{
			DrawDeleteComponentPopup(_collider);

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

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawDirectionalLightComponent(Core::DirectionalLight* _light)
	{
		if (!_light)
			return;

		if (ImGui::TreeNodeEx("Directional Light", m_treeNodeComponentFlags))
		{
			DrawDeleteComponentPopup(_light);

			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawPointLightComponent(Core::PointLight* _light)
	{
		if (!_light)
			return;

		if (ImGui::TreeNodeEx("Point Light", m_treeNodeComponentFlags))
		{
			DrawDeleteComponentPopup(_light);

			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawSpotLightComponent(Core::SpotLight* _light)
	{
		if (!_light)
			return;

		if (ImGui::TreeNodeEx("Spot Light", m_treeNodeComponentFlags))
		{
			DrawDeleteComponentPopup(_light);

			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAddComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("Add Component Popup Window");

		ImGui::SetNextWindowSize(m_alreadyAddComponentWindowSize);
		if (ImGui::BeginPopupContextWindow("Add Component Popup Window", m_PopupAddComponentFlags))
		{
			DrawAddRendererComponent(_crtGOSelected);
			DrawAddColliderComponent(_crtGOSelected);
			DrawAddLightComponent(_crtGOSelected);
			ImGui::EndPopup();
		}

		if (bisComponentAlreadyAddedWindowEnable)
			ImGui::OpenPopup("ComponentAlreadyAddedWindowModal");

		if (ImGui::BeginPopupModal("ComponentAlreadyAddedWindowModal", 0, m_alreadyAddComponentWindowFlags))
		{
			ImGui::Text("This component has already been added to this object!");
			if (ImGui::Button("Close"))
			{
				bisComponentAlreadyAddedWindowEnable = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	void InspectorGUI::DrawAddRendererComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::TreeNodeEx("Renderer", m_treeNodeAddComponentFlags))
		{
			if (ImGui::Button("Model", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::Model* model = _crtGOSelected->GetComponent<Core::Model>();
				if (!model)
				{
					model = _crtGOSelected->AddComponent<Core::Model>();
					Resource::Mesh* mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("Cube.obj");
					Resource::Texture* texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("WhiteTexture.img");
					Resource::ShaderProgram* shader = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>("DefaultDeferredRendering.shd");
					model->SetData(mesh, texture, shader);
				}
				else
				{
					bisComponentAlreadyAddedWindowEnable = true;
				}
				ImGui::CloseCurrentPopup();
			}
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAddColliderComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::TreeNodeEx("Collider", m_treeNodeAddComponentFlags))
		{
			if (ImGui::Button("Box Collider", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::BoxCollider* boxCollider = _crtGOSelected->GetComponent<Core::BoxCollider>();
				if (!boxCollider)
					boxCollider = _crtGOSelected->AddComponent<Core::BoxCollider>();
				else
					bisComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Capsule Collider", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::CapsuleCollider* capsuleCollider = _crtGOSelected->GetComponent<Core::CapsuleCollider>();
				if (!capsuleCollider)
					capsuleCollider = _crtGOSelected->AddComponent<Core::CapsuleCollider>();
				else
					bisComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Mesh Collider", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::MeshCollider* meshCollider = _crtGOSelected->GetComponent<Core::MeshCollider>();
				if (!meshCollider)
					meshCollider = _crtGOSelected->AddComponent<Core::MeshCollider>();
				else
					bisComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAddLightComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::TreeNodeEx("Light", m_treeNodeAddComponentFlags))
		{
			if (ImGui::Button("Directional Light", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::DirectionalLight* directionalLight = _crtGOSelected->GetComponent<Core::DirectionalLight>();
				if (!directionalLight)
					directionalLight = _crtGOSelected->AddComponent<Core::DirectionalLight>();
				else
					bisComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Point Light", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::PointLight* pointLight = _crtGOSelected->GetComponent<Core::PointLight>();
				if (!pointLight)
					pointLight = _crtGOSelected->AddComponent<Core::PointLight>();
				else
					bisComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Spot Light", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::SpotLight* SpotLight = _crtGOSelected->GetComponent<Core::SpotLight>();
				if (!SpotLight)
					SpotLight = _crtGOSelected->AddComponent<Core::SpotLight>();
				else
					bisComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			ImGui::TreePop();
		}
	}
}