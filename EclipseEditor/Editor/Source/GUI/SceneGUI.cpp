#include "GUI/SceneGUI.hpp"
#include "SceneCamera.hpp"
#include "Scene.hpp"
#include "ResourceManager.hpp"
#include <iostream>

namespace GUI
{
	void SceneGUI::Draw(Core::GameObject* _crtGOSelected, Core::SceneCamera* _camera, const unsigned int _textureID, int& _windowWidth, int& _windowHeight, int& _windowPosX, int& _windowPosY)
	{
		ImGui::SetNextWindowSizeConstraints({ 300.f, 300.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags sceneWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Scene", 0, sceneWindowFlags);
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 windowPos = ImGui::GetWindowPos();

		_windowWidth = static_cast<int>(windowSize.x);
		_windowHeight = static_cast<int>(windowSize.y);
		_windowPosX = static_cast<int>(windowPos.x);
		_windowPosY = static_cast<int>(windowPos.y);

		if (_camera->MouseSpeedChanged())
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.75f)); 
			ImGui::SetNextWindowSize(m_windowSizeCameraChangedSpeed);
			ImGui::SetNextWindowPos({ windowPos.x + windowSize.x / 2.f - m_windowSizeCameraChangedSpeed.x / 2.f, windowPos.y + windowSize.y / 2.f - m_windowSizeCameraChangedSpeed.y / 2.f });
			ImGuiWindowFlags mouseSpeedChangedWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration;
			ImGui::Begin("MouseSpeedChangedWindow", 0, mouseSpeedChangedWindowFlags);

			ImGui::SetWindowFontScale(3.f);
			ImGui::Text("%.2f", _camera->GetMouseSpeed());

			ImGui::PopStyleColor();
			ImGui::End();
		}


		ImGui::GetWindowDrawList()->AddImage(
			static_cast<intptr_t>(_textureID),
			ImVec2(windowPos.x, windowPos.y),
			ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
			ImVec2(0, 1),
			ImVec2(1, 0));


		// Editor Buttons
		Resource::Texture* translateText = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("TranslateGizmoIcon.img");
		Resource::Texture* rotateText = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("RotateGizmoIcon.img");
		Resource::Texture* scaleText = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("ScaleGizmoIcon.img");

		ImVec2 uv0{ 0.f, 1.f };
		ImVec2 uv1{ 1.f, 0.f };

		
		ImGui::PushStyleColor(ImGuiCol_Border, { 1.f, 1.f, 1.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.35f, 0.35f, 0.35f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.5f, 0.5f, 0.5f, 1.f });

		// Local & Global
		if (ImGui::Button(m_crtGizmoMode == ImGuizmo::MODE::LOCAL ? "Local" : "Global", { 52.f, 34.f}))
			m_crtGizmoMode = m_crtGizmoMode == ImGuizmo::MODE::LOCAL ? ImGuizmo::MODE::WORLD : ImGuizmo::MODE::LOCAL;
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(m_crtGizmoMode == ImGuizmo::MODE::LOCAL ? "Ctrl + I" : "Ctrl + U");
		
		ImGui::PopStyleColor(1);

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.f, 2.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.f, 1.f, 1.f, 1.f });
		// Translation
		if (ImGui::ImageButton("TranslateImageButton", translateText->GetID(), { 48.f, 30.f }, uv0, uv1, {1.f, 0.f, 0.f, 1.f}))
			m_crtGizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("Ctrl + R");
		}

		// Rotation
		if (ImGui::ImageButton("RotateImageButton", rotateText->GetID(), { 48.f, 30.f }, uv0, uv1))
			m_crtGizmoOperation = ImGuizmo::OPERATION::ROTATE;
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("Ctrl + T");
		}

		// Scale
		if (ImGui::ImageButton("ScaleImageButton", scaleText->GetID(), { 48.f, 30.f }, uv0, uv1))
			m_crtGizmoOperation = ImGuizmo::OPERATION::SCALE;
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("Ctrl + Y");
		}

		ImGui::PopStyleColor(3);
		ImGui::PopStyleVar();

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

		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();

		ImGuizmo::SetDrawlist();
		ImGuizmo::SetOrthographic(false);
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
	}
}