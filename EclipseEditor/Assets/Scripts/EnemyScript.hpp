#pragma once
#include "Scripting/MonoBehaviour.hpp"
#include "Scripting/RegisterTypeMacro.hpp"

class EnemyScript : public Core::MonoBehaviour
{
public:
	EnemyScript();
	~EnemyScript() override;

	void OnStart() override;
	void OnUpdate(Windowing::IWindow* _window, float _deltaTime) override;
	void OnDestroy() override;
	void OnCollisionEnter(Core::ICollider* _collider) override;
	void OnCollisionStay(Core::ICollider* _collider) override;
	void OnCollisionExit(Core::ICollider* _collider) override;
};

REGISTER_TYPE(EnemyScript);