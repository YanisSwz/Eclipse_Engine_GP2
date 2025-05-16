#pragma once
#include "ProjectExports.hpp"
#include "TransformSystem.hpp"
#include "Scripting/ScriptingSystem.hpp"
#include "RenderSystem.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Audio/AudioSystem.hpp"
#include "Camera/CameraSystem.hpp"
#include "Particles/ParticleSystem.hpp"
#include "GameState.hpp"
#include <vector>

namespace Windowing
{
	class IWindow;
}

namespace Core
{
	class Scene;

	class SystemManager
	{
	public:
		ECLIPSE_ENGINE SystemManager();
		ECLIPSE_ENGINE ~SystemManager();

		ECLIPSE_ENGINE void Update(Scene* _scene, Windowing::IWindow* _window, float _deltaTime, GAME_STATE _state, std::unordered_map<std::string, std::function<MonoBehaviour* ()>>& _register);
		ECLIPSE_ENGINE Transform* AddTransform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f }, Transform* _parent = nullptr);
		ECLIPSE_ENGINE Transform* GetTransformsRoot() const;
		ECLIPSE_ENGINE inline RenderSystem* GetRenderSystem() { return &m_renderSystem; };
		ECLIPSE_ENGINE AudioSystem* GetAudioSystem();
		ECLIPSE_ENGINE CameraSystem* GetCameraSystem();
		ECLIPSE_ENGINE ScriptingSystem* GetScriptingSystem();
		ECLIPSE_ENGINE void Render(RHI::IRenderInterface* _renderInterface, RHI::IGraphicPipeline* _pipeline, Math::Mat4 _V, Math::Mat4 _P, Math::Vec3 _viewPos);

		template <typename T>
		T* AddComponent()
		{
			T* basePtr = new T();

			if (Camera* dynamicCamera_ptr = dynamic_cast<Camera*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_cameraSystem.AddCamera());
			}
			else if (Model* dynamicModel_ptr = dynamic_cast<Model*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_renderSystem.AddModel());
			}
			else if (BoxCollider* dynamicBoxCollider_ptr = dynamic_cast<BoxCollider*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_physicsSystem.AddBoxCollider());
			}
			else if (CapsuleCollider* dynamicCapsuleCollider_ptr = dynamic_cast<CapsuleCollider*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_physicsSystem.AddCapsuleCollider());
			}
			else if (MeshCollider* dynamicMeshCollider_ptr = dynamic_cast<MeshCollider*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_physicsSystem.AddMeshCollider());
			}
			else if (DirectionalLight* dynamicDirectionalLight_ptr = dynamic_cast<DirectionalLight*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_renderSystem.AddDirLight());
			}
			else if (PointLight* dynamicPointLight_ptr = dynamic_cast<PointLight*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_renderSystem.AddPointLight());
			}
			else if (SpotLight* dynamicSpotLight_ptr = dynamic_cast<SpotLight*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_renderSystem.AddSpotLight());
			}
			else if (AudioSource* audioSource_ptr = dynamic_cast<AudioSource*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_audioSystem.AddAudioSource());
			}
			else if (AudioListener* audioListener_ptr = dynamic_cast<AudioListener*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_audioSystem.AddAudioListener());
			}
			else if (ParticleEmitter* particleEmitter_ptr = dynamic_cast<ParticleEmitter*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_particleSystem.AddParticleEmitter());
			}
			else if (ScriptComponent* scriptComponent_ptr = dynamic_cast<ScriptComponent*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_scriptingSystem.AddScript());
			}
			delete basePtr;
			return nullptr;
		}

		ECLIPSE_ENGINE Component* AddComponent(std::string _componentType);

		ECLIPSE_ENGINE void Reset();

	private:
		CameraSystem m_cameraSystem{};
		TransformSystem m_transformSystem{};
		ScriptingSystem m_scriptingSystem{};
		RenderSystem m_renderSystem{};
		PhysicsSystem m_physicsSystem{};
		AudioSystem m_audioSystem{};
		ParticleSystem m_particleSystem{};
	};
}