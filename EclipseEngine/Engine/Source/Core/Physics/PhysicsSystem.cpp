#include "Physics/PhysicsSystem.hpp"
#include "Logging/Logger.hpp"

namespace Core
{
	PhysicsSystem::PhysicsSystem()
	{

	}

	PhysicsSystem::~PhysicsSystem()
	{

	}

	BoxCollider* PhysicsSystem::AddBoxCollider(bool _isDynamic, Math::Vec3 _size, Math::Vec3 _pos, Math::Vec3 _rot)
	{
		if (m_currentColliderCount == MAX_COLLIDER_SIZE)
		{
			Logging::Logger::Get()->Log(Logging::PRIORITY::WARNING, "You reach the maximum capacity of colliders!");
			return nullptr;
		}

		for (int i = 0; i < m_currentBoxColliderCount; ++i)
		{
			if (m_boxColliders[i].IsDestroyed())
			{
				m_boxColliders[i].Remove();
				m_boxColliders[i].~BoxCollider();
				new (&m_boxColliders[i]) BoxCollider(_isDynamic, _size, _pos, _rot);
				m_boxColliders[i].SetActive(true);
				return &m_boxColliders[i];
			}
		}

		m_boxColliders[m_currentBoxColliderCount].~BoxCollider();
		new (&m_boxColliders[m_currentBoxColliderCount]) BoxCollider(_isDynamic, _size, _pos, _rot);
		m_boxColliders[m_currentBoxColliderCount].SetActive(true);
		
		++m_currentColliderCount;
		++m_currentBoxColliderCount;
		
		return &m_boxColliders[m_currentBoxColliderCount - 1];
	}
}