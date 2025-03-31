#include "MonoBehaviour.hpp"
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
}