#include "GUI/InspectorGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "GameObject.hpp"

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

		if (_crtGOselected)
		{
			GUI::DragVec3XYZ("Position", _crtGOselected->transform->localPosition);
			GUI::DragQuatXYZ("Rotation", _crtGOselected->transform->localRotation);
			GUI::DragVec3XYZ("Scale", _crtGOselected->transform->localScale, 1.f);
		}

		ImGui::End();
	}
}