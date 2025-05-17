#include "PlayerScript.hpp"
#include "Scene.hpp"
#include "ResourceManager.hpp"

PlayerScript::PlayerScript()
{
}

PlayerScript::~PlayerScript()
{
}

void PlayerScript::OnStart()
{
	m_collider = m_gameObject->GetComponent<Core::BoxCollider>();
	m_source = m_gameObject->GetComponent<Core::AudioSource>();
	m_fireball = Resource::ResourceManager::GetInstance().GetResource<Resource::Prefab>("Fireball.json");
	m_timer = m_attackInterval;
}

void PlayerScript::OnUpdate(Windowing::IWindow* _window, float _deltaTime)
{
	if(m_collider == nullptr)
	{
		Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Could not find collider");
		return;
	}

	m_timer += _deltaTime;

	Math::Vec3 direction{0.f, 0.f, 0.f};
	if (_window->GetKey(Windowing::KEY_CODE::KEY_W, Windowing::INPUT_ACTION::INPUT_DOWN))
		direction += Math::Vec3::forward;
	if (_window->GetKey(Windowing::KEY_CODE::KEY_S, Windowing::INPUT_ACTION::INPUT_DOWN))
		direction -= Math::Vec3::forward;
	if (_window->GetKey(Windowing::KEY_CODE::KEY_A, Windowing::INPUT_ACTION::INPUT_DOWN))
		direction += Math::Vec3::right;
	if (_window->GetKey(Windowing::KEY_CODE::KEY_D, Windowing::INPUT_ACTION::INPUT_DOWN))
		direction -= Math::Vec3::right;

	direction.Normalize();
	// Only Z
	if(direction.z > 0.f && direction.x == 0.f)
		m_collider->SetRotation(Math::Quat::QuaternionAxisAngle(Math::Vec3::up, 0.f));
	else if(direction.z < 0.f && direction.x == 0.f)
		m_collider->SetRotation(Math::Quat::QuaternionAxisAngle(Math::Vec3::up, 180.f));
	// Only X
	else if (direction.x > 0.f && direction.z == 0.f)
		m_collider->SetRotation(Math::Quat::QuaternionAxisAngle(Math::Vec3::up, 90.f));
	else if (direction.x < 0.f && direction.z == 0.f)
		m_collider->SetRotation(Math::Quat::QuaternionAxisAngle(Math::Vec3::up, -90.f));
	// Left Diagonals
	else if (direction.x > 0.f && direction.z > 0.f)
		m_collider->SetRotation(Math::Quat::QuaternionAxisAngle(Math::Vec3::up, 45.f));
	else if (direction.x > 0.f && direction.z < 0.f)
		m_collider->SetRotation(Math::Quat::QuaternionAxisAngle(Math::Vec3::up, 135.f));
	// Right Diagionals
	else if (direction.x < 0.f && direction.z > 0.f)
		m_collider->SetRotation(Math::Quat::QuaternionAxisAngle(Math::Vec3::up, -45.f));
	else if (direction.x < 0.f && direction.z < 0.f)
		m_collider->SetRotation(Math::Quat::QuaternionAxisAngle(Math::Vec3::up, -135.f));

	_deltaTime;
	m_collider->SetVelocity({ direction.x * m_speed, m_collider->GetVelocity().y, direction.z * m_speed });

	if (_window->GetMouseButton(Windowing::MOUSE_CODE::LEFT_BUTTON, Windowing::INPUT_ACTION::INPUT_PRESS))
	{
		if (m_timer >= m_attackInterval)
		{
			m_timer -= m_attackInterval;
			if (m_fireball != nullptr)
			{
				Core::GameObject* fireball = m_scene->InstantiatePrefab(nullptr, m_fireball);
				if (m_fireballCount != 0)
					fireball->name.append(" (" + std::to_string(m_fireballCount) + ")");
				Math::Vec3 pos = m_gameObject->transform->GetPosition();
				fireball->transform->SetPosition(pos + m_gameObject->transform->GetForward() * 4.f - m_gameObject->transform->GetRight() / 2.f);
				fireball->transform->SetRotation(Math::Quat::QuaternionAxisAngle(Math::Vec3::up, -90.f) * m_gameObject->transform->GetRotation());
				++m_fireballCount;
			}
			m_source->Play();
		}
	}
}

void PlayerScript::OnDestroy()
{
}

void PlayerScript::OnCollisionEnter(Core::ICollider* _collider)
{
	if (_collider->GetGameObject()->tag == "Floor")
		Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "Aouch");
}

void PlayerScript::OnCollisionStay(Core::ICollider* _collider)
{
	_collider;
}

void PlayerScript::OnCollisionExit(Core::ICollider* _collider)
{
	_collider;
}