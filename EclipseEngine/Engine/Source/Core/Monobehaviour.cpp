#include "MonoBehaviour.hpp"

namespace Core
{
	void MonoBehaviour::Awake() {};
	void MonoBehaviour::Start() { hasStarted = true; };
	void MonoBehaviour::Update() {};
	void MonoBehaviour::OnDestroy() {};
	void MonoBehaviour::OnEnable() {};
	void MonoBehaviour::OnDisable() {};
}