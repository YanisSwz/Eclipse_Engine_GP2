#include "GUI/SceneGUI.hpp"
#include "SceneCamera.hpp"
#include "Scene.hpp"
#include <iostream>

namespace GUI
{
	SceneGUI::SceneGUI()
	{
	}

	SceneGUI::~SceneGUI()
	{
	}

	void SceneGUI::Draw(Core::GameObject* _crtGOSelected, Core::SceneCamera* _camera, const unsigned int _textureID, int& _windowWidth, int& _windowHeight, int& _windowPosX, int& _windowPosY)
	{
		ImGuiWindowFlags sceneWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Scene", 0, sceneWindowFlags);
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 windowPos = ImGui::GetWindowPos();
		_windowWidth = static_cast<int>(windowSize.x);
		_windowHeight = static_cast<int>(windowSize.y);
		_windowPosX = static_cast<int>(windowPos.x);
		_windowPosY = static_cast<int>(windowPos.y);

		ImGui::GetWindowDrawList()->AddImage(
			static_cast<intptr_t>(_textureID),
			ImVec2(windowPos.x, windowPos.y),
			ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
			ImVec2(0, 1),
			ImVec2(1, 0));

		DrawGizmo(_crtGOSelected, _camera);

		ImGui::End();
	}

	void SceneGUI::StartGizmo()
	{
		ImGuizmo::BeginFrame();
	}

	void SceneGUI::UpdateGizmoMode(Windowing::IWindow* _window)
	{
		if (_window->GetKey(Windowing::KEY_CODE::KEY_CTRL_LEFT, Windowing::INPUT_ACTION::INPUT_DOWN))
		{
			if (_window->GetKey(Windowing::KEY_CODE::KEY_R, Windowing::INPUT_ACTION::INPUT_PRESS))
				m_crtGizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
			else if (_window->GetKey(Windowing::KEY_CODE::KEY_T, Windowing::INPUT_ACTION::INPUT_PRESS))
				m_crtGizmoOperation = ImGuizmo::OPERATION::ROTATE;
			else if (_window->GetKey(Windowing::KEY_CODE::KEY_Y, Windowing::INPUT_ACTION::INPUT_PRESS))
				m_crtGizmoOperation = ImGuizmo::OPERATION::SCALE;


			if (_window->GetKey(Windowing::KEY_CODE::KEY_U, Windowing::INPUT_ACTION::INPUT_PRESS))
				m_crtGizmoMode = ImGuizmo::MODE::LOCAL;
			if (_window->GetKey(Windowing::KEY_CODE::KEY_I, Windowing::INPUT_ACTION::INPUT_PRESS))
				m_crtGizmoMode = ImGuizmo::MODE::WORLD;
		}
	}

	void SceneGUI::DrawGizmo(Core::GameObject* _crtGOSelected, Core::SceneCamera* _camera)
	{
		if (!_crtGOSelected)
			return;

		if (ImGuizmo::IsUsingAny() && !_crtGOSelected->transform->IsSelected())
			_crtGOSelected->transform->StartOverride();
		else if (!ImGuizmo::IsUsingAny() && _crtGOSelected->transform->IsSelected())
			_crtGOSelected->transform->EndOverride();

		float viewManipulateRight = ImGui::GetWindowPos().x + (float)ImGui::GetWindowWidth();
		float viewManipulateTop = ImGui::GetWindowPos().y;
		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();

		ImGuizmo::SetDrawlist();
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetGizmoSizeClipSpace(0.25f);
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

		Math::Mat4 TRS = _crtGOSelected->transform->GetTransformMatrix();
		Math::Mat4 view = _camera->GetView();
		Math::Mat4 proj = _camera->GetProjection();

		TRS.Transpose();
		view.Transpose();
		proj.Transpose();

		if (ImGuizmo::Manipulate(view.GetValuesPointer(), proj.GetValuesPointer(),
			m_crtGizmoOperation, m_crtGizmoMode,
			const_cast<float*>(TRS.GetValuesPointer())))
		{
			float position[3];
			float rotation[3];
			float scale[3];

			ImGuizmo::DecomposeMatrixToComponents(TRS.GetValuesPointer(), position, rotation, scale);

			switch (m_crtGizmoOperation)
			{
			case ImGuizmo::OPERATION::TRANSLATE:
				_crtGOSelected->transform->SetPosition(Math::Vec3(position[0], position[1], position[2]));
				break;

			case ImGuizmo::OPERATION::ROTATE:
			{
				Math::Quat Xquat = Math::Quat::QuaternionAxisAngle(Math::Vec3::right, rotation[0]);
				Math::Quat Yquat = Math::Quat::QuaternionAxisAngle(Math::Vec3::up, rotation[1]);
				Math::Quat Zquat = Math::Quat::QuaternionAxisAngle(Math::Vec3::forward, rotation[2]);
				_crtGOSelected->transform->SetRotation(Zquat * Yquat * Xquat);
				break;
			}

			case ImGuizmo::OPERATION::SCALE:
				_crtGOSelected->transform->SetScale(Math::Vec3(scale[0] * Math::Tools::Sign(_crtGOSelected->transform->GetScale().x), scale[1] * Math::Tools::Sign(_crtGOSelected->transform->GetScale().y), scale[2] * Math::Tools::Sign(_crtGOSelected->transform->GetScale().z)));
				break;
			}

			_crtGOSelected->transform->UpdateOverride();
		}

		ImGuizmo::ViewManipulate(const_cast<float*>(view.GetValuesPointer()), 8.f,
			ImVec2(viewManipulateRight - 128.f, viewManipulateTop + 20.f),
			ImVec2(128.f, 128.f), static_cast<ImU32>(0x00000000));
	}
}