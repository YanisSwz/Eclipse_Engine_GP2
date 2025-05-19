#include "EnemyScript.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Scripting/ScriptComponent.hpp"

EnemyScript::EnemyScript()
{
}

EnemyScript::~EnemyScript()
{
}

void EnemyScript::OnStart()
{
	m_collider = m_gameObject->GetComponent<Core::BoxCollider>();

	m_emitter = m_gameObject->GetComponent<Core::ParticleEmitter>();
	if (m_emitter)
		m_emitter->SetActive(false);

	m_source = m_gameObject->GetComponent<Core::AudioSource>();
	if (m_source)
		m_source->SetActive(false);
	Core::GameObject* player = m_scene->FindByTag("Player");
	if (player && player->GetComponent<Core::ScriptComponent>())
		m_player = dynamic_cast<PlayerScript*>(player->GetComponent<Core::ScriptComponent>()->Instance);
}

void EnemyScript::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	_window;
	_deltaTime;

	if (m_exploding && m_source != nullptr && m_emitter != nullptr)
	{
		if (m_emitter->IsActive() && !m_emitter->IsPlaying() && m_source->IsActive() && !m_source->IsPlaying())
			m_gameObject->Destroy();
	}

	if (!m_exploding && m_player)
	{
		Math::Vec3 direction = m_player->GetGameObject()->transform->GetPosition() - m_gameObject->transform->GetPosition();
		direction.Normalize();

		m_collider->SetVelocity({ direction.x * m_speed, m_collider->GetVelocity().y, direction.z * m_speed });
	}
}

void EnemyScript::OnDestroy()
{
}

void EnemyScript::OnCollisionEnter(Core::ICollider* _collider)
{
	if (_collider->GetGameObject()->tag == "Player")
	{
		if (!m_exploding)
		{
			Explode();
			PlayerScript* player = dynamic_cast<PlayerScript*>(_collider->GetGameObject()->GetComponent<Core::ScriptComponent>()->Instance);
			if (player)
				Explode();
		}
	}
}

void EnemyScript::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void EnemyScript::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}

void EnemyScript::Explode()
{
	m_exploding = true;
	m_gameObject->GetComponent<Core::Model>()->SetActive(false);
	m_speed = 0.f;
	if (m_emitter)
	{
		m_emitter->SetActive(true);
		if (!m_emitter->IsPlaying())
			m_emitter->Play();
	}
	if (m_source)
	{
		m_source->SetActive(true);
		if (!m_source->IsPlaying())
			m_source->Play();
	}
}

void EnemyScript::TakeDamage()
{
	if (m_health >= 0)
	{
		--m_health;
		if (m_health == 0)
			Explode();
	}
}