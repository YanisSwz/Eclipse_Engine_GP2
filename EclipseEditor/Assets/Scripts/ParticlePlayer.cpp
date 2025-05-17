#include "ParticlePlayer.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Core/Particles/ParticleEmitter.hpp"

ParticlePlayer::ParticlePlayer()
{
}

ParticlePlayer::~ParticlePlayer()
{
}

void ParticlePlayer::OnStart()
{
	Core::ParticleEmitter* trail = m_gameObject->GetComponent<Core::ParticleEmitter>();
	if (trail)
		trail->Play();
}

void ParticlePlayer::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	_window;
	_deltaTime;
	if (_window->GetKey(Windowing::KEY_CODE::KEY_W, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + (m_gameObject->transform->GetForward() * speed * _deltaTime));
	if (_window->GetKey(Windowing::KEY_CODE::KEY_S, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() - (m_gameObject->transform->GetForward() * speed * _deltaTime));
	if (_window->GetKey(Windowing::KEY_CODE::KEY_A, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() + (m_gameObject->transform->GetRight() * speed * _deltaTime));
	if (_window->GetKey(Windowing::KEY_CODE::KEY_D, Windowing::INPUT_ACTION::INPUT_DOWN))
		m_gameObject->transform->SetPosition(m_gameObject->transform->GetPosition() - (m_gameObject->transform->GetRight() * speed * _deltaTime));
}

void ParticlePlayer::OnDestroy()
{
}

void ParticlePlayer::OnCollisionEnter(Core::ICollider* _collider)
{
	_collider;
}

void ParticlePlayer::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void ParticlePlayer::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}