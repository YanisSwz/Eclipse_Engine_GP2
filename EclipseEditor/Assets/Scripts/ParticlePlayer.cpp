#include "ParticlePlayer.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"

ParticlePlayer::ParticlePlayer()
{
}

ParticlePlayer::~ParticlePlayer()
{
}

void ParticlePlayer::OnStart()
{
	m_trail = m_gameObject->GetComponent<Core::ParticleEmitter>();
	if (m_trail)
		m_trail->Play();

	std::vector<Core::Transform*> transforms = m_scene->GetSystemManager()->GetTransformsRoot()->GetChildren();
	for (Core::Transform* transform : transforms)
		GetParticleEmitters(transform);
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


	if (_window->GetKey(Windowing::KEY_CODE::KEY_SPACE, Windowing::INPUT_ACTION::INPUT_PRESS))
	{
		if (bIsParticlesPlaying)
		{
			for (Core::ParticleEmitter* emitter : m_emitters)
				emitter->Stop();
			if (m_trail)
				m_trail->Play();
			bIsParticlesPlaying = false;
		}
		else
		{
			for (Core::ParticleEmitter* emitter : m_emitters)
				emitter->Play();
			if (m_trail)
				m_trail->Play();
			bIsParticlesPlaying = true;
		}
	}
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

void ParticlePlayer::GetParticleEmitters(Core::Transform* _transform)
{
	Core::ParticleEmitter* emitter = _transform->GetGameObject()->GetComponent<Core::ParticleEmitter>();
	if (emitter)
		m_emitters.push_back(emitter);

	for (Core::Transform* child : _transform->GetChildren())
		GetParticleEmitters(child);
}