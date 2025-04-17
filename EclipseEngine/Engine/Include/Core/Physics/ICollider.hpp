#pragma once
#include "Core/Component.hpp"
#include "Maths.hpp"
#include "ProjectExports.hpp"
//#include <Jolt/Jolt.h>
//#include <Jolt/Physics/Body/BodyCreationSettings.h>

namespace Core
{
	class GameObject;

	class ICollider : public Component
	{
	public:
		ICollider() = default;
		virtual ~ICollider() = default;

		Math::Vec3 position = { 0.f, 0.f, 0.f };
		bool b_isDynamic = false;

		virtual void Delete() = 0;

	private:
		//JPH::BodyID m_bodyID;
	};
}