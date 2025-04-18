#pragma once
#include "Core/Component.hpp"
#include "Maths.hpp"
#include "ProjectExports.hpp"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include "Core/Physics/Layers.hpp"

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

		ECLIPSE_ENGINE void SetDynamic(bool _isDynamic);
		ECLIPSE_ENGINE void SetPosition(float _posX, float _posY, float _posZ);
		ECLIPSE_ENGINE void SetPosition(Math::Vec3 _position);
		ECLIPSE_ENGINE Math::Vec3 GetPosition() const;
		virtual void Delete() = 0;

	protected:
		JPH::BodyInterface* m_bodyInterface = nullptr;
		JPH::BodyID m_bodyID;
	};
}