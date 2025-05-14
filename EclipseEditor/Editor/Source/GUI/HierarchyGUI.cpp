#include "GUI/HierarchyGUI.hpp"
#include "GUI/ContentBrowserGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"
#include "vector"
#include "Scene.hpp"

namespace GUI
{
	Core::GameObject* HierarchyGUI::Draw(Core::Scene* _scene, Core::GameObject* _crtGOSelected, ContentBrowserGUI* _contentBrowser)
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
			std::vector<Core::Transform*> transforms = _scene->GetSystemManager()->GetTransformsRoot()->GetChildren();
			for (Core::Transform* transform : transforms)
			{
				Core::GameObject* tempNewGOSelected = RecursiveDraw(transform, _scene, _crtGOSelected, _contentBrowser);
				if (tempNewGOSelected)
					newGameObjectSelected = tempNewGOSelected;
			}

			ImGui::TreePop();
		}

		ImGui::End();
		return newGameObjectSelected;
	}

	Core::GameObject* HierarchyGUI::RecursiveDraw(Core::Transform* _crtTransform, Core::Scene* _scene, Core::GameObject* _crtGOSelected, ContentBrowserGUI* _contentBrowser)
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
						Resource::Prefab* prefab = Resource::ResourceManager::GetInstance().GetResource<Resource::Prefab>("prefab.json");
						if (!prefab)
						{
							prefab = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Prefab>("prefab.json", "Assets/Prefabs/prefab.json");
							Resource::ResourceManager::GetInstance().LoadAllResources();
							if (_contentBrowser)
								_contentBrowser->AddPrefab(prefab);
						}
						_scene->SavePrefab(_crtGOSelected, prefab);
						ImGui::CloseCurrentPopup();
					}
					if (ImGui::Button("Instantiate Prefab"))
					{
						_scene->InstantiatePrefab(newGameObjectSelected, Resource::ResourceManager::GetInstance().GetResource<Resource::Prefab>("prefab.json"));
						ImGui::CloseCurrentPopup();
					}
				}
				ImGui::EndPopup();
			}
			for (Core::Transform* transform : transforms)
			{
				Core::GameObject* tempNewGOSelected = RecursiveDraw(transform, _scene, _crtGOSelected, _contentBrowser);
				if (tempNewGOSelected)
					newGameObjectSelected = tempNewGOSelected;
			}

			ImGui::TreePop();

			//if (ImGui::BeginPopupModal())
			//{
			//	std::vector<std::string> prefabNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Prefab>();
			//	std::string prefabName;
			//	if (GUI::ComboFilter("Mesh ", &prefabName, prefabNames))
			//		
			//	if (ImGui::BeginDragDropTarget())
			//	{
			//		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MeshName"))
			//		{
			//			IM_ASSERT(payload->DataSize == sizeof(std::string));
			//			std::string payload_n;
			//			payload_n = *static_cast<std::string*>(payload->Data);
			//			_model->SetMesh(Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(payload_n));
			//		}
			//		ImGui::EndDragDropTarget();
			//	}
			//}
		}
		else
		{
			if (!_crtTransform->GetGameObject()->IsActive())
				ImGui::PopStyleVar();
		}
		return newGameObjectSelected;
	}
}