#pragma once
#include <imgui.h>

namespace Core
{
	class GameObject;
	class Transform;
	class Model;
	class BoxCollider;
	class CapsuleCollider;
	class MeshCollider;
	class DirectionalLight;
	class PointLight;
	class SpotLight;
}

namespace GUI
{
	class InspectorGUI
	{
	public:
		InspectorGUI();
		~InspectorGUI() = default;

		void Draw(Core::GameObject* _crtGOSelected);

	private:
		void DrawTransformComponent(Core::Transform* _transform);
		void DrawModelComponent(Core::Model* _model);
		void DrawBoxColliderComponent(Core::BoxCollider* _collider);
		void DrawCapsuleColliderComponent(Core::CapsuleCollider* _collider);
		void DrawMeshColliderComponent(Core::MeshCollider* _collider);
		void DrawDirectionalLightComponent(Core::DirectionalLight* _light);
		void DrawPointLightComponent(Core::PointLight* _light);
		void DrawSpotLightComponent(Core::SpotLight* _light);

		void DrawAddComponent(Core::GameObject* _crtGOSelected);
		void DrawAddRendererComponent(Core::GameObject* _crtGOSelected);
		void DrawAddColliderComponent(Core::GameObject* _crtGOSelected);
		void DrawAddLightComponent(Core::GameObject* _crtGOSelected);

		ImGuiTreeNodeFlags m_treeNodeComponentFlags = ImGuiTreeNodeFlags_None;
		ImGuiTreeNodeFlags m_treeNodeAddComponentFlags = ImGuiTreeNodeFlags_None;
		ImGuiPopupFlags m_PopupAddComponentFlags = ImGuiPopupFlags_None;
		
		ImGuiWindowFlags m_alreadyAddComponentWindowFlags = ImGuiWindowFlags_None;
		ImVec2 m_alreadyAddComponentWindowSize{ 300.f, 400.f };
		bool bisComponentAlreadyAddedWindowEnable = false;
	};
}