#pragma once
#include "Scripting/MonoBehaviour.hpp"
#include "Scripting/RegisterTypeMacro.hpp"
#include "Physics/BoxCollider.hpp"
#include "Audio/AudioSource.hpp"
#include "Resource/Prefab.hpp"

class PlayerScript : public Core::MonoBehaviour
{
public:
	PlayerScript();
	~PlayerScript() override;

	void OnStart() override;
	void OnUpdate(Windowing::IWindow* _window, float _deltaTime) override;
	void OnDestroy() override;
	void OnCollisionEnter(Core::ICollider* _collider) override;
	void OnCollisionStay(Core::ICollider* _collider) override;
	void OnCollisionExit(Core::ICollider* _collider) override;

private:
	Core::BoxCollider* m_collider = nullptr;
	Core::AudioSource* m_source = nullptr;
	Resource::Prefab* m_fireball = nullptr;
	float m_speed = 10.f;
	int m_fireballCount = 0;
	float m_timer = 0.f;
	float m_attackInterval = 0.75f;
};

REGISTER_TYPE(PlayerScript);