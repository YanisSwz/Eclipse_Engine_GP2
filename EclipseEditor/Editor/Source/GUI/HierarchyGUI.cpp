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

		std::vector<Core::Transform*> transforms = _scene->GetSystemManager()->GetTransformsRoot()->GetChildren();
		for (Core::Transform* transform : transforms)
		{
			Core::GameObject* tempNewGOSelected = RecursiveDraw(transform, _scene, _crtGOSelected);
			if (tempNewGOSelected)
				newGameObjectSelected = tempNewGOSelected;
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
			treeNodeFlags |= ImGuiTreeNodeFlags_Bullet;

		if (ImGui::TreeNodeEx(_crtTransform->GetGameObject()->name.c_str(), treeNodeFlags))
		{
			if (ImGui::IsItemClicked())
				newGameObjectSelected = _crtTransform->GetGameObject();

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
		return newGameObjectSelected;
	}
}