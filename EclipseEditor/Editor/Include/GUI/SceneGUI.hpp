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

namespace Resource
{
	class Texture;
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
		ImVec2 m_windowSizeCameraChangedSpeed{ 100.f, 100.f };
		std::vector<std::string> GizmoOperatorsString{ "Translate", "Rotation", "Scale" };

		Resource::Texture* m_translateBtnTexture = nullptr;
		Resource::Texture* m_rotateBtnTexture = nullptr;
		Resource::Texture* m_scaleBtnTexture = nullptr;

		void DrawGizmo(Core::GameObject* _crtGOSelected, Core::SceneCamera* _camera);
	};
}