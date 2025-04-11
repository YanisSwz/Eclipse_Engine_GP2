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
		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

		//Dirty ImGui test for scene graph hierarchy
		std::vector<Core::Transform*> transforms = _scene->GetTransforms()->GetChildren();
		if (ImGui::TreeNodeEx("root", treeNodeFlags))
		{
			treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;
			for (Core::Transform* transform : transforms)
			{
				if (transform->GetGameObject() == _crtGOSelected)
					treeNodeFlags |= ImGuiTreeNodeFlags_Selected;

				if (ImGui::TreeNodeEx(transform->GetGameObject()->GetName().c_str(), treeNodeFlags))
					ImGui::TreePop();

				if (ImGui::IsItemClicked())
					_crtGOSelected = transform->GetGameObject();
				treeNodeFlags &= ~ImGuiTreeNodeFlags_Selected;
			}
			ImGui::TreePop();
		}

		ImGui::End();
		return _crtGOSelected;
	}
}