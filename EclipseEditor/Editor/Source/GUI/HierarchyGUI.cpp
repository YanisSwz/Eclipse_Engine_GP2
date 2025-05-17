#include "GUI/HierarchyGUI.hpp"
#include "GUI/ContentBrowserGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Prefab.hpp"
#include <vector>
#include "Scene.hpp"

namespace GUI
{
	Core::GameObject* HierarchyGUI::Draw(Core::Scene* _scene, Core::GameObject* _crtGOSelected)
	{
		Core::GameObject* newGameObjectSelected = nullptr;

		ImGui::SetNextWindowSizeConstraints({ 200.f, 100.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags hierarchyWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Hierarchy", 0, hierarchyWindowFlags);
		
		if (ImGui::BeginPopupContextWindow("HierarchyPopUpMenu"))
		{
			if (ImGui::Button("Add Node"))
			{
				newGameObjectSelected = _scene->CreateGameObject();
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		if (ImGui::TreeNodeEx(_scene->GetName().c_str(), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TransformDrag"))
				{
					IM_ASSERT(payload->DataSize == sizeof(int));
					int* payload_n;
					payload_n = static_cast<int*>(payload->Data);
					Core::Transform* transform = _scene->GetObjectByID(*payload_n)->transform;
					_scene->GetSystemManager()->GetTransformsRoot()->AddChild(transform);
					transform->SetPosition(transform->GetPosition());
					transform->SetRotation(transform->GetRotation());
					transform->SetScale(transform->GetScale());
				}

				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PrefabName"))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::string));
					m_crtPrefabName = *static_cast<std::string*>(payload->Data);

					m_crtPrefab = Resource::ResourceManager::GetInstance().GetResource<Resource::Prefab>(m_crtPrefabName);
					_scene->InstantiatePrefab(nullptr, m_crtPrefab);
					m_crtPrefabName.clear();
					m_crtPrefab = nullptr;
				}
				ImGui::EndDragDropTarget();
			}
			
			std::vector<Core::Transform*> transforms = _scene->GetSystemManager()->GetTransformsRoot()->GetChildren();
			for (Core::Transform* transform : transforms)
			{
				Core::GameObject* tempNewGOSelected = RecursiveDraw(transform, _scene, _crtGOSelected);
				if (tempNewGOSelected)
					newGameObjectSelected = tempNewGOSelected;
			}

			ImGui::TreePop();
		}

		ImGui::End();
		return newGameObjectSelected;
	}

	Core::GameObject* HierarchyGUI::RecursiveDraw(Core::Transform* _crtTransform, Core::Scene* _scene, Core::GameObject* _crtGOSelected)
	{
		Core::GameObject* newGameObjectSelected = nullptr;

		std::vector<Core::Transform*> transforms = _crtTransform->GetChildren();
		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		if (transforms.size() == 0)
			treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;

		if (_crtTransform->GetGameObject() == _crtGOSelected)
			treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

		if (!_crtTransform->GetGameObject()->IsActive())
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);

		if (ImGui::TreeNodeEx(_crtTransform->GetGameObject()->name.c_str(), treeNodeFlags))
		{
			if (ImGui::IsItemClicked())
				newGameObjectSelected = _crtTransform->GetGameObject();

			if (!_crtTransform->GetGameObject()->IsActive())
				ImGui::PopStyleVar();


			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("TransformDrag", &_crtTransform->GetGameObject()->GetIDRef(), sizeof(int));
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TransformDrag"))
				{
					IM_ASSERT(payload->DataSize == sizeof(int));
					int* payload_n;
					payload_n = static_cast<int*>(payload->Data);
					Core::Transform* transform = _scene->GetObjectByID(*payload_n)->transform;
					transform->SetParent(_crtTransform);
					transform->SetPosition(transform->GetPosition());
					transform->SetRotation(transform->GetRotation());
					transform->SetScale(transform->GetScale());
				}

				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PrefabName"))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::string));
					m_crtPrefabName = *static_cast<std::string*>(payload->Data);

					m_crtPrefab = Resource::ResourceManager::GetInstance().GetResource<Resource::Prefab>(m_crtPrefabName);
					_scene->InstantiatePrefab(_crtTransform->GetGameObject(), m_crtPrefab);
					m_crtPrefabName.clear();
					m_crtPrefab = nullptr;
				}

				ImGui::EndDragDropTarget();
			}


			if (ImGui::BeginPopupContextItem("HierarchyPopUpMenu"))
			{
				newGameObjectSelected = _crtTransform->GetGameObject();
				if (ImGui::Button("Add Node"))
				{
					if (_crtGOSelected)
					{
						newGameObjectSelected = _scene->CreateGameObject();
						newGameObjectSelected->transform->SetParent(_crtGOSelected->transform);
						ImGui::CloseCurrentPopup();
					}
					else
					{
						newGameObjectSelected = _scene->CreateGameObject();
						ImGui::CloseCurrentPopup();
					}
				}

				if (_crtGOSelected)
				{
					if (ImGui::Button("Delete Node"))
						_crtGOSelected->Destroy();

					if (ImGui::Button("Save as Prefab"))
					{
						bIsPrefabWindowOpen = true;
						bIsPrefabInstantiate = false;
						ImGui::OpenPopup("Prefab Selection");
						ImGui::SetNextWindowSize(ImVec2(250, 150));
					}
				}

				if (ImGui::Button("Instantiate Prefab"))
				{
					bIsPrefabWindowOpen = true;
					bIsPrefabInstantiate = true;
					ImGui::OpenPopup("Prefab Selection");
					ImGui::SetNextWindowSize(ImVec2(250, 150));
				}

				if (ImGui::BeginPopupModal("Prefab Selection"))
				{
					std::vector<std::string> prefabNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Prefab>();

					GUI::ComboFilter("Prefab", &m_crtPrefabName, prefabNames);

					if (bIsPrefabInstantiate)
					{
						m_crtPrefab = Resource::ResourceManager::GetInstance().GetResource<Resource::Prefab>(m_crtPrefabName);
						if (ImGui::Button("Instantiate") && m_crtPrefab)
						{
							_scene->InstantiatePrefab(_crtGOSelected, m_crtPrefab);
							m_crtPrefabName.clear();
							m_crtPrefab = nullptr;
							bIsPrefabWindowOpen = false;
							ImGui::CloseCurrentPopup();
						}
					}
					else
					{
						m_crtPrefab = Resource::ResourceManager::GetInstance().GetResource<Resource::Prefab>(m_crtPrefabName);
						if (ImGui::Button("Save") && m_crtPrefab)
						{
							_scene->SavePrefab(_crtGOSelected, m_crtPrefab);
							m_crtPrefabName.clear();
							m_crtPrefab = nullptr;
							bIsPrefabWindowOpen = false;
							ImGui::CloseCurrentPopup();
						}
					}
					ImGui::SameLine();
					if (ImGui::Button("Cancel"))
					{
						m_crtPrefabName.clear();
						m_crtPrefab = nullptr;
						bIsPrefabWindowOpen = false;
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				ImGui::EndPopup();
			}
			for (Core::Transform* transform : transforms)
			{
				Core::GameObject* tempNewGOSelected = RecursiveDraw(transform, _scene, _crtGOSelected);
				if (tempNewGOSelected)
					newGameObjectSelected = tempNewGOSelected;
			}

			ImGui::TreePop();
		}
		else
		{
			if (!_crtTransform->GetGameObject()->IsActive())
				ImGui::PopStyleVar();
		}
		return newGameObjectSelected;
	}
}