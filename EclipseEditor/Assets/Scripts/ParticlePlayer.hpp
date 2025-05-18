#pragma once
#include "Scripting/MonoBehaviour.hpp"
#include "Scripting/RegisterTypeMacro.hpp"
#include "Core/Particles/ParticleEmitter.hpp"
#include "Core/Transform.hpp"
#include <vector>

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

	Core::ParticleEmitter* m_trail;
	std::vector<Core::ParticleEmitter*> m_emitters;
	bool bIsParticlesPlaying = false;

	void GetParticleEmitters(Core::Transform* _transform);
};

REGISTER_TYPE(ParticlePlayer);