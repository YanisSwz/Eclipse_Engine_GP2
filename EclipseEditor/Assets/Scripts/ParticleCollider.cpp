#include "ParticleCollider.hpp"
#include "GameObject.hpp"

ParticleCollider::ParticleCollider()
{
}

ParticleCollider::~ParticleCollider()
{
}

void ParticleCollider::OnStart()
{
	std::vector<Core::Transform*> children = m_gameObject->transform->GetChildren();
	Core::ParticleEmitter* emitter;
	for (Core::Transform* child : children)
	{
		emitter = child->GetGameObject()->GetComponent<Core::ParticleEmitter>();
		if (emitter)
		{
			emitter->Stop();
			m_particleEmitters.push_back(emitter);
		}
	}
}

void ParticleCollider::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	_window;
	_deltaTime;
}

void ParticleCollider::OnDestroy()
{
}

void ParticleCollider::OnCollisionEnter(Core::ICollider* _collider)
{
	if (_collider->GetGameObject()->tag == "Player")
	{
		for (Core::ParticleEmitter* emitter : m_particleEmitters)
			emitter->Play();
	}
}

void ParticleCollider::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void ParticleCollider::OnCollisionExit(Core::ICollider* _collider)
{
	if (_collider->GetGameObject()->tag == "Player")
	{
		for (Core::ParticleEmitter* emitter : m_particleEmitters)
			emitter->Stop();
	}
}