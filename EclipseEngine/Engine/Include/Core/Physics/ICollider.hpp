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

		ECLIPSE_ENGINE void SetActive(bool _activate) override;
		ECLIPSE_ENGINE virtual void SetDynamic(bool _isDynamic);
		virtual void SetMass(float _mass) = 0;
		ECLIPSE_ENGINE void AddForce(float _forceX, float _forceY, float _forceZ);
		ECLIPSE_ENGINE void AddForce(Math::Vec3 _force);
		ECLIPSE_ENGINE void AddForce(Math::Vec3 _dir, float _force);
		ECLIPSE_ENGINE void AddImpulse(float _impulseX, float _impulseY, float _impulseZ);
		ECLIPSE_ENGINE void AddImpulse(Math::Vec3 _impulse);
		ECLIPSE_ENGINE void AddImpulse(Math::Vec3 _dir, float _impulse);
		ECLIPSE_ENGINE void AddBodyToPhysicsEngine();
		ECLIPSE_ENGINE void RemoveBodyToPhysicsEngine();

		ECLIPSE_ENGINE void SetPosition(float _posX, float _posY, float _posZ);
		ECLIPSE_ENGINE void SetPosition(Math::Vec3 _position);
		ECLIPSE_ENGINE void SetRotation(float _rotX, float _rotY, float _rotZ);
		ECLIPSE_ENGINE void SetRotation(Math::Vec3 _rotation);
		ECLIPSE_ENGINE void SetRotation(Math::Quat _rotation);
		virtual void Scale(float _scaleX, float _scaleY, float _scaleZ) = 0;
		virtual void Scale(Math::Vec3 _scale) = 0;
		ECLIPSE_ENGINE void SetPosRot(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ);
		ECLIPSE_ENGINE void SetPosRot(Math::Vec3 _position, Math::Vec3 _rotation);
		ECLIPSE_ENGINE void SetPosRot(Math::Vec3 _position, Math::Quat _rotation);
		ECLIPSE_ENGINE void SetPosRotScale(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ, float _scaleX, float _scaleY, float _scaleZ);
		ECLIPSE_ENGINE void SetPosRotScale(Math::Vec3 _position, Math::Vec3 _rotation, Math::Vec3 _scale);
		ECLIPSE_ENGINE void SetOffsetPos(float _offsetPosX, float _offsetPosY, float _offsetPosZ);
		ECLIPSE_ENGINE void SetOffsetPos(Math::Vec3 _offsetPos);
		ECLIPSE_ENGINE void SetVelocity(Math::Vec3 _velocity);

		ECLIPSE_ENGINE Math::Vec3 GetPosition() const;
		ECLIPSE_ENGINE Math::Vec3 GetOffsetPos() const;
		ECLIPSE_ENGINE Math::Vec3 GetOffsetPosRotated() const;
		ECLIPSE_ENGINE Math::Quat GetRotation() const;
		ECLIPSE_ENGINE Math::Vec3 GetScale() const;
		ECLIPSE_ENGINE float GetMass() const;
		ECLIPSE_ENGINE bool GetIsDynamic() const;
		ECLIPSE_ENGINE JPH::BodyID GetBodyID() const;
		ECLIPSE_ENGINE Math::Vec3 GetVelocity() const;

		ECLIPSE_ENGINE void Destroy() override;
		ECLIPSE_ENGINE void Delete();

		virtual void Serialize(json& _j) override = 0;
		virtual void Deserialize(const json& _j) override = 0;

	protected:
		Math::Vec3 m_position = { 0.f, 0.f, 0.f };
		Math::Vec3 m_offsetPos = { 0.f, 0.f, 0.f };
		Math::Quat m_rotation = { 0.f, 0.f, 0.f, 0.f };
		Math::Vec3 m_scale = { 1.f, 1.f, 1.f };
		float m_mass = 1.f;
		bool b_isDynamic = false;
		bool b_isBodyDestroyed = true;

		JPH::BodyInterface* m_bodyInterface = nullptr;
		JPH::BodyID m_bodyID;

		void UpdateData();
		virtual void Recreate() = 0;
	};
}