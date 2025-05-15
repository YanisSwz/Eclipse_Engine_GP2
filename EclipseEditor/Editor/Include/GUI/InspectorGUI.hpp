#pragma once
#include "Maths.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>

namespace Core
{
	class GameObject;
	class Component;
	class Transform;
	class Camera;
	class Model;
	class BoxCollider;
	class CapsuleCollider;
	class MeshCollider;
	class DirectionalLight;
	class PointLight;
	class SpotLight;
	class AudioSource;
	class AudioListener;
	class ParticleEmitter;
	class ScriptComponent;
}

namespace Resource
{
	class Texture;
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
		bool DrawDeleteComponentPopup(Core::Component* _component);
		void DrawTransformComponent(Core::Transform* _transform);
		void DrawCameraComponent(Core::Camera* _camera);
		void DrawModelComponent(Core::Model* _model);
		void DrawBoxColliderComponent(Core::BoxCollider* _collider);
		void DrawCapsuleColliderComponent(Core::CapsuleCollider* _collider);
		void DrawMeshColliderComponent(Core::MeshCollider* _collider);
		void DrawDirectionalLightComponent(Core::DirectionalLight* _light);
		void DrawPointLightComponent(Core::PointLight* _light);
		void DrawSpotLightComponent(Core::SpotLight* _light);
		void DrawAudioSourceComponent(Core::AudioSource* _source);
		void DrawAudioListenerComponent(Core::AudioListener* _listener);
		void DrawParticleEmitterComponent(Core::ParticleEmitter* _particleEmitter);
		void DrawScriptComponent(Core::ScriptComponent* _scriptComponent);

		void DrawAddComponent(Core::GameObject* _crtGOSelected);
		void DrawAddCameraComponent(Core::GameObject* _crtGOSelected);
		void DrawAddRendererComponent(Core::GameObject* _crtGOSelected);
		void DrawAddColliderComponent(Core::GameObject* _crtGOSelected);
		void DrawAddLightComponent(Core::GameObject* _crtGOSelected);
		void DrawAddAudioComponent(Core::GameObject* _crtGOSelected);
		void DrawAddParticlesComponent(Core::GameObject* _crtGOSelected);
		void DrawAddScriptComponent(Core::GameObject* _crtGOSelected);

		ImGuiTreeNodeFlags m_treeNodeComponentFlags = ImGuiTreeNodeFlags_None;
		ImGuiTreeNodeFlags m_treeNodeAddComponentFlags = ImGuiTreeNodeFlags_None;
		ImGuiPopupFlags m_PopupAddComponentFlags = ImGuiPopupFlags_None;
		
		ImGuiWindowFlags m_alreadyAddComponentWindowFlags = ImGuiWindowFlags_None;
		ImVec2 m_alreadyAddComponentWindowSize{ 300.f, 400.f };
		bool bIsComponentAlreadyAddedWindowEnable = false;
		bool bIsScaleLocked = false;
		Math::Vec3 m_scaleFactor{ 1.f, 1.f, 1.f };
		const int MAX_NAME_SIZE = 50;
		std::string m_newTagName;
		const int MAX_TAG_NAME_SIZE = 20;
		const int SCRIPT_NAME_MAX_SIZE = 20;
		std::string m_newScriptName = "";
		ImVec2 m_addingScriptWindowSize{ 350.f, 110.f };
		bool bIsAddingScript = false;

		Resource::Texture* m_playBtnTexture = nullptr;
		Resource::Texture* m_stopBtnTexture = nullptr;
		Resource::Texture* m_pauseBtnTexture = nullptr;
	};
}