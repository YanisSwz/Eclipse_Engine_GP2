#pragma once
#include "GUI/Widget/ImGuiWidget.hpp"
#include "../ImGuizmo/ImGuizmo.h"

namespace Core
{
	class SceneCamera;
	class GameObject;
}

namespace Windowing
{
	class IWindow;
}

namespace GUI
{
	class SceneGUI
	{
	public:
		SceneGUI();
		~SceneGUI();

		void Draw(Core::GameObject* _crtGOSelected, Core::SceneCamera* _camera, const unsigned int _textureID, int& _windowWidth, int& _windowHeight, int& _windowPosX, int& _windowPosY);
		void StartGuizmo();
		void UpdateGuizmoMode(Windowing::IWindow* _window);

	private:
		ImGuizmo::OPERATION m_crtGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		ImGuizmo::MODE m_crtGuizmoMode = ImGuizmo::MODE::LOCAL;

		void DrawGuizmo(Core::GameObject* _crtGOSelected, Core::SceneCamera* _camera);
	};
}