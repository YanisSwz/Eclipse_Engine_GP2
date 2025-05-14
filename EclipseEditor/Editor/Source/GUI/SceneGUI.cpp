#include "GUI/SceneGUI.hpp"
#include "SceneCamera.hpp"
#include "Scene.hpp"
#include "ResourceManager.hpp"
#include <iostream>

namespace GUI
{
	void SceneGUI::Draw(Core::GameObject* _crtGOSelected, Core::GameObject* _gameObjectPicked, Core::SceneCamera* _camera, const unsigned int _textureID, int& _windowWidth, int& _windowHeight, int& _windowPosX, int& _windowPosY)
	{
		ImGui::SetNextWindowSizeConstraints({ 300.f, 300.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags sceneWindowFlags = ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar;
		ImGui::Begin("Scene", 0, sceneWindowFlags);
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 windowPos = ImGui::GetWindowPos();

		_windowWidth = static_cast<int>(windowSize.x);
		_windowHeight = static_cast<int>(windowSize.y);
		_windowPosX = static_cast<int>(windowPos.x);
		_windowPosY = static_cast<int>(windowPos.y);

		if (_camera->MouseSpeedChanged())
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.95f));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(.75f, .75f, .75f, 0.95f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 2.f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 3.f);
			ImGui::SetNextWindowSize(m_windowSizeCameraChangedSpeed);
			ImGui::SetNextWindowPos({ windowPos.x + windowSize.x / 2.f - m_windowSizeCameraChangedSpeed.x / 2.f, windowPos.y + windowSize.y / 2.f - m_windowSizeCameraChangedSpeed.y / 2.f });
			ImGuiWindowFlags mouseSpeedChangedWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar;
			ImGui::Begin("MouseSpeedChangedWindow", 0, mouseSpeedChangedWindowFlags);

			ImGui::SetWindowFontScale(2.f);
			float windowWidth = ImGui::GetWindowSize().x;
			float textWidth = 0.f;
			if(_camera->GetMouseSpeed() < 10.f)
				textWidth = ImGui::CalcTextSize("5.50").x;
			else
				textWidth = ImGui::CalcTextSize("10.00").x;
			ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
			ImGui::SetCursorPosY(m_windowSizeCameraChangedSpeed.y/2.f - ImGui::GetFontSize()/2.f);
			ImGui::Text("%.2f", _camera->GetMouseSpeed());

			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar(2);
			ImGui::End();
		}

		ImGui::SetCursorPos({ 0.f, 0.f });
		ImVec2 uv0{ 0.f, 1.f };
		ImVec2 uv1{ 1.f, 0.f };
		ImGui::Image(static_cast<intptr_t>(_textureID),
			ImVec2(windowSize.x, windowSize.y),
			uv0, uv1 );

		// Drag & Drop Resource Target
		if (_gameObjectPicked)
		{
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MeshName", ImGuiDragDropFlags_AcceptBeforeDelivery))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::string));
					std::string payload_n = *static_cast<std::string*>(payload->Data);

					Core::Model* modelComponent = _gameObjectPicked->GetComponent<Core::Model>();
					if (modelComponent)
						modelComponent->SetMesh(Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(payload_n));
				}

				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TextureName", ImGuiDragDropFlags_AcceptBeforeDelivery))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::string));
					std::string payload_n = *static_cast<std::string*>(payload->Data);

					Core::Model* modelComponent = _gameObjectPicked->GetComponent<Core::Model>();
					if (modelComponent)
						modelComponent->SetTexture(Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(payload_n));
				}
				ImGui::EndDragDropTarget();
			}
		}

		ImGui::SetItemAllowOverlap();
		ImGui::SetCursorPos({ 8.f, 38.f });

		// Editor Buttons
		if (!m_translateBtnTexture)
			m_translateBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("TranslateGizmoIcon.img");
		if (!m_rotateBtnTexture)
			m_rotateBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("RotateGizmoIcon.img");
		if (!m_scaleBtnTexture)
			m_scaleBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("ScaleGizmoIcon.img");

		ImGui::PushStyleColor(ImGuiCol_Border, { 1.f, 1.f, 1.f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.35f, 0.35f, 0.35f, 1.f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.5f, 0.5f, 0.5f, 1.f });

		// Local & Global
		if (ImGui::Button(m_crtGizmoMode == ImGuizmo::MODE::LOCAL ? "Local" : "Global", { 52.f, 34.f }))
			m_crtGizmoMode = m_crtGizmoMode == ImGuizmo::MODE::LOCAL ? ImGuizmo::MODE::WORLD : ImGuizmo::MODE::LOCAL;
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(m_crtGizmoMode == ImGuizmo::MODE::LOCAL ? "Ctrl + I" : "Ctrl + U");

		ImGui::PopStyleColor(1);

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.f, 2.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.f, 1.f, 1.f, 1.f });
		// Translation
		if (m_translateBtnTexture)
		{
			if (ImGui::ImageButton("TranslateImageButton", m_translateBtnTexture->GetID(), { 48.f, 30.f }, uv0, uv1, { 1.f, 0.f, 0.f, 1.f }))
				m_crtGizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Ctrl + R");
			}
		}

		// Rotation
		if (m_rotateBtnTexture)
		{
			if (ImGui::ImageButton("RotateImageButton", m_rotateBtnTexture->GetID(), { 48.f, 30.f }, uv0, uv1))
				m_crtGizmoOperation = ImGuizmo::OPERATION::ROTATE;
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Ctrl + T");
			}
		}

		// Scale
		if (m_scaleBtnTexture)
		{
			if (ImGui::ImageButton("ScaleImageButton", m_scaleBtnTexture->GetID(), { 48.f, 30.f }, uv0, uv1))
				m_crtGizmoOperation = ImGuizmo::OPERATION::SCALE;
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Ctrl + Y");
			}
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
				_crtGOSelected->transform->SetPosition(position[0], position[1], position[2]);
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
				_crtGOSelected->transform->SetScale(scale[0] * Math::Tools::Sign(_crtGOSelected->transform->GetScale().x), scale[1] * Math::Tools::Sign(_crtGOSelected->transform->GetScale().y), scale[2] * Math::Tools::Sign(_crtGOSelected->transform->GetScale().z));
				break;
			}

			_crtGOSelected->transform->UpdateOverride();
		}
	}
}