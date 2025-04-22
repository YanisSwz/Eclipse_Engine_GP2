#include "Physics/CapsuleCollider.hpp"

// Jolt Includes
#include <Jolt/Jolt.h>
#include <Jolt/Physics/EActivation.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

using namespace JPH::literals;

namespace Core
{
	CapsuleCollider::CapsuleCollider()
	{
	}

	CapsuleCollider::CapsuleCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic, float _mass, float _height, float _radius, Math::Vec3 _pos, Math::Vec3 _rot, GameObject* _myGameObject)
	{
		b_isBodyDestroyed = false;
		m_bodyInterface = _bodyInterface;
		b_isDynamic = _isDynamic;
		m_mass = _mass;
		m_height = _height;
		m_radius = _radius;
		m_position = _pos;
		m_rotation = Math::Quat::QuaternionEuler(_rot.x, _rot.y, _rot.z);
		m_gameObject = _myGameObject;

		JPH::CapsuleShapeSettings shapeSettings(m_height * 0.5f, m_radius);
		shapeSettings.SetEmbedded();
		JPH::ShapeSettings::ShapeResult shapeResult = shapeSettings.Create();
		JPH::ShapeRefC shape = shapeResult.Get();
		JPH::BodyCreationSettings bodySettings(
			shape,
			JPH::RVec3(m_position.x, m_position.y, m_position.z),
			JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }),
			b_isDynamic ? JPH::EMotionType::Dynamic : JPH::EMotionType::Static,
			b_isDynamic ? JPH::Layers::MOVING : JPH::Layers::NON_MOVING);

		bodySettings.mAllowDynamicOrKinematic = true;
		bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
		bodySettings.mMassPropertiesOverride.mMass = m_mass;

		JPH::Body* body = m_bodyInterface->CreateBody(bodySettings);
		m_bodyID = body->GetID();
		m_bodyInterface->AddBody(m_bodyID, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
	}

	CapsuleCollider::~CapsuleCollider()
	{
		Delete();
	}

	void CapsuleCollider::SetMass(float _mass)
	{
		m_mass = _mass;
		Recreate();
	}

	void CapsuleCollider::ScaleHeight(float _height)
	{
		m_height = _height;
		Recreate();
	}

	void CapsuleCollider::ScaleRadius(float _radius)
	{
		m_radius = _radius;
		Recreate();
	}

	void CapsuleCollider::ScaleHeightRadius(float _height, float _radius)
	{
		m_height = _height;
		m_radius = _radius;
		Recreate();
	}

	void CapsuleCollider::SetPosRotHeightRadius(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ, float _height, float _radius)
	{
		SetPosRot({ _posX, _posY, _posZ }, Math::Vec3{ _rotX, _rotY, _rotZ });
		ScaleHeightRadius(_height, _radius);
	}

	void CapsuleCollider::SetPosRotHeightRadius(Math::Vec3 _position, Math::Vec3 _rotation, float _height, float _radius)
	{
		SetPosRot(_position, _rotation);
		ScaleHeightRadius(_height, _radius);
	}

	void CapsuleCollider::Recreate()
	{
		Core::GameObject* gameObject = m_gameObject;
		UpdateData();
		this->~CapsuleCollider();
		new (this) CapsuleCollider(m_bodyInterface, b_isDynamic, m_mass, m_height, m_radius, m_position, m_rotation.GetEulerAnglesRadXYZ(), gameObject);
	}
}