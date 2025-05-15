#pragma once
#include "Scripting/MonoBehaviour.hpp"
#include "Scripting/RegisterTypeMacro.hpp"
#include "Physics/BoxCollider.hpp"

class PlayerScript : public Core::MonoBehaviour
{
public:
	PlayerScript();
	~PlayerScript() override;

	void OnStart() override;
	void OnUpdate(Windowing::IWindow* _window, float _deltaTime) override;
	void OnDestroy() override;
	void OnCollisionEnter(Core::ICollider* _collider) override;
	void OnCollisionStay(Core::ICollider* _collider) override;
	void OnCollisionExit(Core::ICollider* _collider) override;

private:
	Core::BoxCollider* m_collider = nullptr;
};

REGISTER_TYPE(PlayerScript);