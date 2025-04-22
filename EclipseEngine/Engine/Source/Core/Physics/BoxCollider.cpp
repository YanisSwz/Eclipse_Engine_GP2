#include "Physics/BoxCollider.hpp"

// Jolt Includes
#include <Jolt/Jolt.h>
#include <Jolt/Physics/EActivation.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
using namespace JPH::literals;

namespace Core
{
	BoxCollider::BoxCollider()
	{
	}

	BoxCollider::BoxCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic, float _mass, Math::Vec3 _size, Math::Vec3 _pos, Math::Vec3 _rot, GameObject* _myGameObject)
	{
		m_bodyInterface = _bodyInterface;
		b_isDynamic = _isDynamic;
		m_mass = _mass;
		m_position = _pos;
		m_rotation = Math::Quat::QuaternionEuler(_rot.x, _rot.y, _rot.z);
		m_scale = _size;
		m_gameObject = _myGameObject;

		JPH::BoxShapeSettings shapeSettings(JPH::Vec3(m_scale.x * 0.5f, m_scale.y * 0.5f, m_scale.z * 0.5f));
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

	BoxCollider::~BoxCollider()
	{
		Delete();
	}

	void BoxCollider::SetMass(float _mass)
	{
		m_mass = _mass;
		Recreate();
	}

	void BoxCollider::SetScale(float _scaleX, float _scaleY, float _scaleZ)
	{
		if (m_bodyInterface->GetShape(m_bodyID)->IsValidScale({ _scaleX, _scaleY, _scaleZ }))
		{
			UpdateData();
			this->~BoxCollider();
			new (this) BoxCollider(m_bodyInterface, b_isDynamic, m_mass, { _scaleX, _scaleY, _scaleZ }, m_position, m_rotation.GetEulerAnglesRadXYZ(), m_gameObject);
			// TODO Use ScaleShape
		}
	}

	void BoxCollider::SetScale(Math::Vec3 _scale)
	{
		if (m_bodyInterface->GetShape(m_bodyID)->IsValidScale({ _scale.x, _scale.y, _scale.z }))
		{
			UpdateData();
			this->~BoxCollider();
			new (this) BoxCollider(m_bodyInterface, b_isDynamic, m_mass, _scale, m_position, m_rotation.GetEulerAnglesRadXYZ(), m_gameObject);
			// TODO Use ScaleShape
		}
	}

	void BoxCollider::SetPosRotScale(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ, float _scaleX, float _scaleY, float _scaleZ)
	{
		if (m_bodyInterface->GetShape(m_bodyID)->IsValidScale({ _scaleX, _scaleY, _scaleZ }))
		{
			this->~BoxCollider();
			new (this) BoxCollider(m_bodyInterface, b_isDynamic, m_mass, { _scaleX, _scaleY, _scaleZ }, { _posX, _posY, _posZ }, { _rotX, _rotY, _rotZ }, m_gameObject);
		}
	}

	void BoxCollider::SetPosRotScale(Math::Vec3 _position, Math::Vec3 _rotation, Math::Vec3 _scale)
	{
		if (m_bodyInterface->GetShape(m_bodyID)->IsValidScale({ _scale.x, _scale.y, _scale.z }))
		{
			this->~BoxCollider();
			new (this) BoxCollider(m_bodyInterface, b_isDynamic, m_mass, _scale, _position, _rotation, m_gameObject);
		}
	}

	Math::Vec3 BoxCollider::GetScale() const
	{
		return m_scale;
	}

	void BoxCollider::UpdateData()
	{
		m_position = GetPosition();
		m_rotation = GetRotation();
	}

	void BoxCollider::Recreate()
	{
		Core::GameObject* gameObject = m_gameObject;
		UpdateData();
		this->~BoxCollider();
		new (this) BoxCollider(m_bodyInterface, b_isDynamic, m_mass, m_scale, m_position, m_rotation.GetEulerAnglesRadXYZ(), gameObject);
	}
}