#include "PlayerScript.hpp"
#include "GameObject.hpp"

PlayerScript::PlayerScript()
{
}

PlayerScript::~PlayerScript()
{
}

void PlayerScript::OnStart()
{
	m_collider = m_gameObject->GetComponent<Core::BoxCollider>();
}

void PlayerScript::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	float speed = 5.f;
	if (_window->GetKey(Windowing::KEY_CODE::KEY_W, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + Math::Vec3{ 0.f, 0.f, 1.f } *_deltaTime * speed);
	if (_window->GetKey(Windowing::KEY_CODE::KEY_S, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + Math::Vec3{ 0.f, 0.f, -1.f } *_deltaTime * speed);
	if (_window->GetKey(Windowing::KEY_CODE::KEY_A, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + Math::Vec3{ 1.f, 0.f, 0.f } *_deltaTime * speed);
	if (_window->GetKey(Windowing::KEY_CODE::KEY_D, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + Math::Vec3{ -1.f, 0.f, 0.f } *_deltaTime * speed);
}

void PlayerScript::OnDestroy()
{
}

void PlayerScript::OnCollisionEnter(Core::ICollider* _collider)
{
	_collider;
}

void PlayerScript::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void PlayerScript::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}