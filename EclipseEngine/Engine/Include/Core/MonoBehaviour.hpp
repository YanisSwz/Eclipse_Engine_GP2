#pragma once
#include "ProjectExports.hpp"
#include "Component.hpp"

namespace Core 
{
	class ICollider;

	class MonoBehaviour : public Component
	{
	public:
		ECLIPSE_ENGINE MonoBehaviour();
		ECLIPSE_ENGINE virtual ~MonoBehaviour() = default;

		ECLIPSE_ENGINE virtual void Awake();
		ECLIPSE_ENGINE virtual void OnEnable();
		ECLIPSE_ENGINE virtual void Start();
		ECLIPSE_ENGINE virtual void Update();
		ECLIPSE_ENGINE virtual void OnDisable();
		ECLIPSE_ENGINE virtual void OnDestroy();

		ECLIPSE_ENGINE virtual void OnCollisionEnter(ICollider* _collider);
		ECLIPSE_ENGINE virtual void OnCollisionStay(ICollider* _collider);
		ECLIPSE_ENGINE virtual void OnCollisionExit(ICollider* _collider);

	protected:
		bool hasStarted = false;
	};
}