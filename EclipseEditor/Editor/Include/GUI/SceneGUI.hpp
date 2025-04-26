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
		SceneGUI() = default;
		~SceneGUI() = default;

		void Draw(Core::GameObject* _crtGOSelected, Core::SceneCamera* _camera, const unsigned int _textureID, int& _windowWidth, int& _windowHeight, int& _windowPosX, int& _windowPosY);
		void StartGizmo();
		void UpdateGizmoMode(Windowing::IWindow* _window);

	private:
		ImGuizmo::OPERATION m_crtGizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		ImGuizmo::MODE m_crtGizmoMode = ImGuizmo::MODE::LOCAL;

		void DrawGizmo(Core::GameObject* _crtGOSelected, Core::SceneCamera* _camera);
	};
}