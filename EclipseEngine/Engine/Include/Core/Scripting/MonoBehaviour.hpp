#pragma once
#include "ProjectExports.hpp"
#include "Windowing/IWindow.hpp"
#include "Core/Physics/ICollider.hpp"

namespace Core 
{
	class GameObject;
	class Scene;

	class MonoBehaviour
	{
	public:
		ECLIPSE_ENGINE MonoBehaviour() = default;
		ECLIPSE_ENGINE virtual ~MonoBehaviour() = 0;


		ECLIPSE_ENGINE virtual void OnStart();
		ECLIPSE_ENGINE virtual void OnUpdate(Windowing::IWindow* _window, float _deltaTime);
		ECLIPSE_ENGINE virtual void OnDestroy();

		ECLIPSE_ENGINE virtual void OnCollisionEnter(ICollider* _collider);
		ECLIPSE_ENGINE virtual void OnCollisionStay(ICollider* _collider);
		ECLIPSE_ENGINE virtual void OnCollisionExit(ICollider* _collider);

	protected:
		Scene* m_scene = nullptr;
		GameObject* m_gameObject = nullptr;
		friend class ScriptingSystem;
	};
}