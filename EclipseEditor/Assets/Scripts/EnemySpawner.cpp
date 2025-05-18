#include "EnemySpawner.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "ResourceManager.hpp"

EnemySpawner::EnemySpawner()
{
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::OnStart()
{
	m_enemyPrefab = Resource::ResourceManager::GetInstance().GetResource<Resource::Prefab>("BasicEnemy.json");
	m_emitter = m_gameObject->GetComponent<Core::ParticleEmitter>();
}

void EnemySpawner::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	_window;
	if (!m_deactivated)
	{
		m_timer += _deltaTime;

		if (m_timer >= m_duration && m_enemyCount < m_enemyNb)
		{
			m_timer = 0.f;
			SpawnEnemy();
		}
	}
	else
	{
		if (m_emitter && !m_emitter->IsPlaying())
			m_gameObject->Destroy();
	}
}

void EnemySpawner::OnDestroy()
{
}

void EnemySpawner::OnCollisionEnter(Core::ICollider* _collider)
{
	_collider;
}

void EnemySpawner::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void EnemySpawner::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}

void EnemySpawner::SpawnEnemy()
{
	if (m_enemyPrefab)
	{
		++m_enemyCount;
		if (m_emitter)
			m_emitter->Play();

		Core::GameObject* enemy = m_scene->InstantiatePrefab(nullptr, m_enemyPrefab);
		enemy->transform->SetPosition(m_gameObject->transform->GetPosition());

		if (m_enemyCount == m_enemyNb)
			m_deactivated = true;
	}
}