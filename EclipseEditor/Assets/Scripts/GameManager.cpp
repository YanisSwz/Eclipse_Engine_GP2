#include "GameManager.hpp"
#include "GameObject.hpp"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::OnStart()
{
}

void GameManager::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	_window;
	_deltaTime;
}

void GameManager::OnDestroy()
{
}

void GameManager::OnCollisionEnter(Core::ICollider* _collider)
{
	_collider;
}

void GameManager::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void GameManager::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}