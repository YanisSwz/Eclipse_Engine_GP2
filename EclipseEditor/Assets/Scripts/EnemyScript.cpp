#include "EnemyScript.hpp"
#include "GameObject.hpp"

EnemyScript::EnemyScript()
{
}

EnemyScript::~EnemyScript()
{
}

void EnemyScript::OnStart()
{
}

void EnemyScript::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	_window;
	_deltaTime;
}

void EnemyScript::OnDestroy()
{
}

void EnemyScript::OnCollisionEnter(Core::ICollider* _collider)
{
	_collider;
}

void EnemyScript::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void EnemyScript::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}