#include "MonoBehaviour.hpp"
#include "Core/Physics/ICollider.hpp"
#include <iostream>

namespace Core
{
	MonoBehaviour::MonoBehaviour() { Awake(); }
	void MonoBehaviour::Awake() {};
	void MonoBehaviour::Start() { hasStarted = true; };

	void MonoBehaviour::Update() 
	{
		if (!hasStarted)
		{
			Start();
			return;
		}
	};

	void MonoBehaviour::OnDestroy() {};
	void MonoBehaviour::OnEnable() {};
	void MonoBehaviour::OnDisable() {};

	void MonoBehaviour::OnCollisionEnter(ICollider* _collider) {};
	void MonoBehaviour::OnCollisionStay(ICollider* _collider) {};
	void MonoBehaviour::OnCollisionExit(ICollider* _collider) {};
}