#pragma once
#include "Scripting/MonoBehaviour.hpp"
#include "Scripting/RegisterTypeMacro.hpp"
#include "ProjectExports.hpp"

namespace Windowing
{
	class IWindow;
}

class TestScript : public Core::MonoBehaviour
{
public:

	ECLIPSE_ENGINE TestScript() = default;
	ECLIPSE_ENGINE ~TestScript() = default;

	ECLIPSE_ENGINE void OnStart() override;
	ECLIPSE_ENGINE void OnUpdate(Windowing::IWindow* _window, float _deltaTime) override;
	ECLIPSE_ENGINE void OnDestroy() override;
	ECLIPSE_ENGINE void OnCollisionEnter(Core::ICollider* _collider) override;
	ECLIPSE_ENGINE void OnCollisionStay(Core::ICollider* _collider) override;
	ECLIPSE_ENGINE void OnCollisionExit(Core::ICollider* _collider) override;

	const char* playerName = "Player";
	int life = 10;
	const int MaxLife = 20;
};

REGISTER_TYPE(TestScript);