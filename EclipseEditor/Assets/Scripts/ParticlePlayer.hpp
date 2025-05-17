#pragma once
#include "Scripting/MonoBehaviour.hpp"
#include "Scripting/RegisterTypeMacro.hpp"

class ParticlePlayer : public Core::MonoBehaviour
{
public:
	ParticlePlayer();
	~ParticlePlayer() override;

	void OnStart() override;
	void OnUpdate(Windowing::IWindow* _window, float _deltaTime) override;
	void OnDestroy() override;
	void OnCollisionEnter(Core::ICollider* _collider) override;
	void OnCollisionStay(Core::ICollider* _collider) override;
	void OnCollisionExit(Core::ICollider* _collider) override;
private:
	float speed = 5.0f;
};

REGISTER_TYPE(ParticlePlayer);