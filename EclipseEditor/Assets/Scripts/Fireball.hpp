#pragma once
#include "Scripting/MonoBehaviour.hpp"
#include "Scripting/RegisterTypeMacro.hpp"
#include "Particles/ParticleEmitter.hpp"
#include "Audio/AudioSource.hpp"
#include "Physics/BoxCollider.hpp"

class Fireball : public Core::MonoBehaviour
{
public:
	Fireball();
	~Fireball() override;

	void OnStart() override;
	void OnUpdate(Windowing::IWindow* _window, float _deltaTime) override;
	void OnDestroy() override;
	void OnCollisionEnter(Core::ICollider* _collider) override;
	void OnCollisionStay(Core::ICollider* _collider) override;
	void OnCollisionExit(Core::ICollider* _collider) override;
	void Explode();

private:
	Core::BoxCollider* m_collider = nullptr;
	Core::ParticleEmitter* m_emitter = nullptr;
	Core::AudioSource* m_source = nullptr;
	float m_speed = 30.f;
	float m_timer = 0.f;
	float m_duration = 1.5f;
	float m_originalY = 0.f;
	bool m_exploding = false;

};

REGISTER_TYPE(Fireball);