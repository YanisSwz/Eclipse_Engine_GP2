#include "Fireball.hpp"
#include "GameObject.hpp"
#include "EnemyScript.hpp"
#include "Scripting/ScriptComponent.hpp"

Fireball::Fireball()
{
}

Fireball::~Fireball()
{
}

void Fireball::OnStart()
{
	m_emitter = m_gameObject->GetComponent<Core::ParticleEmitter>();
	if (m_emitter != nullptr)
		m_emitter->SetActive(false);

	m_source = m_gameObject->GetComponent<Core::AudioSource>();
	if (m_source != nullptr)
		m_source->SetActive(false);

	m_collider = m_gameObject->GetComponent<Core::BoxCollider>();
	m_originalY = m_gameObject->transform->GetPosition().y;
}

void Fireball::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	_window;
	m_timer += _deltaTime;
	if (m_timer >= m_duration)
	{
		if (!m_exploding)
			Explode();
	}
	if (m_source != nullptr && m_emitter != nullptr)
	{
		if (m_emitter->IsActive() && !m_emitter->IsPlaying() && m_source->IsActive() && !m_source->IsPlaying())
			m_gameObject->Destroy();
	}
	Math::Vec3 pos = m_gameObject->transform->GetPosition() + m_gameObject->transform->GetRight() * m_speed * _deltaTime;
	m_gameObject->transform->SetPosition(pos.x, m_originalY, pos.z);
}

void Fireball::OnDestroy()
{
}

void Fireball::OnCollisionEnter(Core::ICollider* _collider)
{
	if (_collider->GetGameObject()->tag == "Enemy")
	{
		if (!m_exploding)
		{
			Explode();
			Core::ScriptComponent* script = _collider->GetGameObject()->GetComponent<Core::ScriptComponent>();
			if (script)
			{
				EnemyScript* enemy = dynamic_cast<EnemyScript*>(script->Instance);
				if (enemy)
					enemy->TakeDamage();
			}
		}
	}
}

void Fireball::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void Fireball::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}

void Fireball::Explode()
{
	m_exploding = true;
	m_gameObject->GetComponent<Core::Model>()->SetActive(false);
	m_gameObject->GetComponent<Core::PointLight>()->SetActive(false);
	m_speed = 0.f;
	if (m_emitter != nullptr)
	{
		m_emitter->SetActive(true);
		if (!m_emitter->IsPlaying())
			m_emitter->Play();
	}
	if (m_source != nullptr)
	{
		m_source->SetActive(true);
		if (!m_source->IsPlaying())
			m_source->Play();
	}
}