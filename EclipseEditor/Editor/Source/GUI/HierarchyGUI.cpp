#include "GUI/HierarchyGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "vector"
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
					_scene->GetSystemManager()->GetTransformsRoot()->AddChild(_scene->GetObjectByID(*payload_n)->transform);
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
					_scene->GetObjectByID(*payload_n)->transform->SetParent(_crtTransform);
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