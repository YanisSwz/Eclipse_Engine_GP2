#include "GUI/HierarchyGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "vector"
#include "Scene.hpp"

namespace GUI
{
	Core::GameObject* HierarchyGUI::Draw(Core::Scene* _scene, Core::GameObject* _crtGOSelected)
	{
		ImGui::SetNextWindowSizeConstraints({ 200.f, 100.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags hierarchyWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Hierarchy", 0, hierarchyWindowFlags);

		std::vector<Core::Transform*> transforms = _scene->GetSystemManager()->GetTransformsRoot()->GetChildren();
		for (Core::Transform* transform : transforms)
		{
			Core::GameObject* newGOSelected = RecursiveDraw(transform, _scene, _crtGOSelected);
			if (newGOSelected)
			{
				ImGui::End();
				return newGOSelected;
			}
		}

		if (ImGui::Button("Add Game Object"))
		{
			if (_crtGOSelected != nullptr)
				_scene->CreateGameObject()->transform->SetParent(_crtGOSelected->transform);
			else
				_scene->CreateGameObject();
		}

		if (ImGui::Button("Destroy Game Object"))
		{
			if(_crtGOSelected != nullptr)
				_crtGOSelected->Destroy();
		}

		ImGui::End();
		return nullptr;
	}

	Core::GameObject* HierarchyGUI::RecursiveDraw(Core::Transform* _crtTransform, Core::Scene* _scene, Core::GameObject* _crtGOSelected)
	{
		std::vector<Core::Transform*> transforms = _crtTransform->GetChildren();
		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		if (transforms.size() == 0)
			treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;

		if (_crtTransform->GetGameObject() == _crtGOSelected)
			treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

		if (ImGui::TreeNodeEx(_crtTransform->GetGameObject()->GetName().c_str(), treeNodeFlags))
		{
			if (ImGui::IsItemClicked())
			{
				ImGui::TreePop();
				return _crtTransform->GetGameObject();
			}

			for (Core::Transform* transform : transforms)
			{
				Core::GameObject* newGOSelected = RecursiveDraw(transform, _scene, _crtGOSelected);
				if (newGOSelected)
				{
					ImGui::TreePop();
					return newGOSelected;
				}
			}
			
			ImGui::TreePop();
		}
		return nullptr;
	}
}