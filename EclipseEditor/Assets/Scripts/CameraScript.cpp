#include "CameraScript.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"

CameraScript::CameraScript()
{
}

CameraScript::~CameraScript()
{
}

void CameraScript::OnStart()
{
	m_player = m_scene->FindByTag("Player");
}

void CameraScript::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	_window;
	_deltaTime;
	if (m_player != nullptr)
	{
		Math::Vec3 playerPos = m_player->transform->GetPosition();
		m_gameObject->transform->SetPosition(playerPos.x, m_gameObject->transform->GetPosition().y, playerPos.z - m_zOffset);
	}
}

void CameraScript::OnDestroy()
{
}

void CameraScript::OnCollisionEnter(Core::ICollider* _collider)
{
	_collider;
}

void CameraScript::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void CameraScript::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}