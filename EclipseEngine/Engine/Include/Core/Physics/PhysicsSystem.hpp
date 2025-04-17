#pragma once
#include "Physics/BoxCollider.hpp"
#include "ProjectExports.hpp"
#include <vector>

namespace Core
{
	class PhysicsSystem
	{
	public:
		ECLIPSE_ENGINE PhysicsSystem();
		ECLIPSE_ENGINE ~PhysicsSystem();
		ECLIPSE_ENGINE BoxCollider* AddBoxCollider(bool _isDynamic = false, Math::Vec3 _size = { 1.f, 1.f, 1.f }, Math::Vec3 _pos = { 0.f, 0.f, 0.f }, Math::Vec3 _rot = { 0.f, 0.f, 0.f });

	private:
		static const int MAX_COLLIDER_SIZE = 1;
		int m_currentColliderCount = 0;
		int m_currentBoxColliderCount = 0;
		BoxCollider m_boxColliders[MAX_COLLIDER_SIZE];
	};
}