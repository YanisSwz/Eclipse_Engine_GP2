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

		bool b_isDynamic = false;

		ECLIPSE_ENGINE void SetDynamic(bool _isDynamic);
		 virtual void SetMass(float _mass) = 0;
		ECLIPSE_ENGINE void SetPosition(float _posX, float _posY, float _posZ);
		ECLIPSE_ENGINE void SetPosition(Math::Vec3 _position);
		ECLIPSE_ENGINE void SetRotation(float _rotX, float _rotY, float _rotZ);
		ECLIPSE_ENGINE void SetRotation(Math::Vec3 _rotation);
		ECLIPSE_ENGINE void SetRotation(Math::Quat _rotation);
		ECLIPSE_ENGINE void SetPosRot(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ);
		ECLIPSE_ENGINE void SetPosRot(Math::Vec3 _position, Math::Vec3 _rotation);
		ECLIPSE_ENGINE void SetPosRot(Math::Vec3 _position, Math::Quat _rotation);
		ECLIPSE_ENGINE Math::Vec3 GetPosition() const;
		ECLIPSE_ENGINE Math::Quat GetRotation() const;
		ECLIPSE_ENGINE float GetMass() const;
		ECLIPSE_ENGINE void Delete();

	protected:
		Math::Vec3 m_position = { 0.f, 0.f, 0.f };
		Math::Quat m_rotation = { 0.f, 0.f, 0.f };
		float m_mass = 3.f;

		JPH::BodyInterface* m_bodyInterface = nullptr;
		JPH::BodyID m_bodyID;

		void UpdateData();
	};
}