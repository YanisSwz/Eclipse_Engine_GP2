#pragma once
#include "Scripting/MonoBehaviour.hpp"
#include "Scripting/RegisterTypeMacro.hpp"
#include "Prefab.hpp"
#include "Particles/ParticleEmitter.hpp"

class EnemySpawner : public Core::MonoBehaviour
{
public:
	EnemySpawner();
	~EnemySpawner() override;

	void OnStart() override;
	void OnUpdate(Windowing::IWindow* _window, float _deltaTime) override;
	void OnDestroy() override;
	void OnCollisionEnter(Core::ICollider* _collider) override;
	void OnCollisionStay(Core::ICollider* _collider) override;
	void OnCollisionExit(Core::ICollider* _collider) override;

private:
	Resource::Prefab* m_enemyPrefab = nullptr;
	Core::ParticleEmitter* m_emitter = nullptr;
	float m_timer = 0.f;
	float m_duration = 5.f;
	int m_enemyNb = 3;
	int m_enemyCount = 0;
	bool m_deactivated = false;
	
	void SpawnEnemy();
};

REGISTER_TYPE(EnemySpawner);