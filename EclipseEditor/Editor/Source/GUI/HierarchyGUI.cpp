#include "GUI/HierarchyGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "vector"
#include "Scene.hpp"

namespace GUI
{
	HierarchyGUI::HierarchyGUI()
	{
	}

	HierarchyGUI::~HierarchyGUI()
	{
	}

	Core::GameObject* HierarchyGUI::Draw(Core::Scene* _scene, Core::GameObject* _crtGOSelected)
	{
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

		ImGui::End();
		return nullptr;
	}

	Core::GameObject* HierarchyGUI::RecursiveDraw(Core::Transform* _crtTransform, Core::Scene* _scene, Core::GameObject* _crtGOSelected)
	{
		//Dirty ImGui test for scene graph hierarchy
		std::vector<Core::Transform*> transforms = _crtTransform->GetChildren();
		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
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