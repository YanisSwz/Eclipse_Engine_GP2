#pragma once
#include "ProjectExports.hpp"
#include "TransformSystem.hpp"
#include "RenderSystem.hpp"
#include "Physics/PhysicsSystem.hpp"
#include "Audio/AudioSystem.hpp"
#include "Camera/CameraSystem.hpp"
#include "GameState.hpp"
#include <vector>

namespace Core
{
	class SystemManager
	{
	public:
		ECLIPSE_ENGINE SystemManager();
		ECLIPSE_ENGINE ~SystemManager();

		ECLIPSE_ENGINE void Update(float _deltaTime, GAME_STATE _state);
		ECLIPSE_ENGINE Transform* AddTransform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f }, Transform* _parent = nullptr);
		ECLIPSE_ENGINE Transform* GetTransformsRoot() const;
		ECLIPSE_ENGINE AudioSystem* GetAudioSystem();
		ECLIPSE_ENGINE CameraSystem* GetCameraSystem();
		ECLIPSE_ENGINE void Render(RHI::IRenderInterface* _renderInterface, RHI::IGraphicPipeline* _pipeline, Math::Mat4 _VP, Math::Vec3 _viewPos);

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
				audioSource_ptr = m_audioSystem.Add();
				return dynamic_cast<T*>(m_audioSystem.Add());
			}
			delete basePtr;
			return nullptr;
		}

	private:
		CameraSystem m_cameraSystem{};
		TransformSystem m_transformSystem{};
		RenderSystem m_renderSystem{};
		PhysicsSystem m_physicsSystem{};
		AudioSystem m_audioSystem{};
	};
}