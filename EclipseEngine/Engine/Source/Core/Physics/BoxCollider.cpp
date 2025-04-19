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

	BoxCollider::BoxCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic, Math::Vec3 _size, Math::Vec3 _pos, Math::Vec3 _rot)
	{
		m_bodyInterface = _bodyInterface;
		b_isDynamic = _isDynamic;
		m_position = _pos;
		m_rotation = Math::Quat::QuaternionEuler(_rot.x, _rot.y, _rot.z);
		m_scale = _size;

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

		JPH::Body* body = m_bodyInterface->CreateBody(bodySettings);
		m_bodyID = body->GetID();
		m_bodyInterface->AddBody(m_bodyID, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
	}

	BoxCollider::~BoxCollider()
	{
		Delete();
	}

	void BoxCollider::SetRotation(float _rotX, float _rotY, float _rotZ)
	{
		m_rotation = Math::Quat::QuaternionEuler(_rotX, _rotY, _rotZ);
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetRotation(m_bodyID, JPH::Quat::sEulerAngles({ m_position.x, m_position.y, m_position.z }), isActivate);
	}

	void BoxCollider::SetRotation(Math::Vec3 _rotation)
	{
		m_rotation = Math::Quat::QuaternionEuler(_rotation.x, _rotation.y, _rotation.z);
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetRotation(m_bodyID, JPH::Quat::sEulerAngles({ m_position.x, m_position.y, m_position.z }), isActivate);
	}

	void BoxCollider::SetScale(float _scaleX, float _scaleY, float _scaleZ)
	{
		if (m_bodyInterface->GetShape(m_bodyID)->IsValidScale({ _scaleX, _scaleY, _scaleZ }))
		{
			UpdateData();
			this->~BoxCollider();
			new (this) BoxCollider(m_bodyInterface, b_isDynamic, { _scaleX, _scaleY, _scaleZ }, m_position, m_rotation.GetEulerAnglesRadXYZ());
			// TODO Use ScaleShape
		}
	}

	void BoxCollider::SetScale(Math::Vec3 _scale)
	{
		if (m_bodyInterface->GetShape(m_bodyID)->IsValidScale({ _scale.x, _scale.y, _scale.z }))
		{
			UpdateData();
			this->~BoxCollider();
			new (this) BoxCollider(m_bodyInterface, b_isDynamic, _scale, m_position, m_rotation.GetEulerAnglesRadXYZ());
			// TODO Use ScaleShape
		}
	}

	void BoxCollider::SetPosRot(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ)
	{
		SetPosition(_posX, _posY, _posZ);
		SetRotation(_rotX, _rotY, _rotZ);
	}

	void BoxCollider::SetPosRot(Math::Vec3 _position, Math::Vec3 _rotation)
	{
		SetPosition(_position);
		SetRotation(_rotation);
	}
	
	void BoxCollider::SetPosRotScale(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ, float _scaleX, float _scaleY, float _scaleZ)
	{
		if (m_bodyInterface->GetShape(m_bodyID)->IsValidScale({ _scaleX, _scaleY, _scaleZ }))
		{
			this->~BoxCollider();
			new (this) BoxCollider(m_bodyInterface, b_isDynamic, { _scaleX, _scaleY, _scaleZ }, { _posX, _posY, _posZ }, { _rotX, _rotY, _rotZ });
		}
	}

	void BoxCollider::SetPosRotScale(Math::Vec3 _position, Math::Vec3 _rotation, Math::Vec3 _scale)
	{
		if (m_bodyInterface->GetShape(m_bodyID)->IsValidScale({ _scale.x, _scale.y, _scale.z }))
		{
			this->~BoxCollider();
			new (this) BoxCollider(m_bodyInterface, b_isDynamic, _scale, _position, _rotation);
		}
	}

	Math::Quat BoxCollider::GetRotation() const
	{
		JPH::Quat rot = m_bodyInterface->GetRotation(m_bodyID);
		return { rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ() };
	}

	Math::Vec3 BoxCollider::GetScale() const
	{
		return m_scale;
	}

	void BoxCollider::Delete()
	{
		if (m_bodyInterface)
		{
			if (m_bodyInterface->IsAdded(m_bodyID))
				m_bodyInterface->RemoveBody(m_bodyID);
			if (m_bodyID.IsInvalid())
				m_bodyInterface->DestroyBody(m_bodyID);
		}
	}

	void BoxCollider::UpdateData()
	{
		m_position = GetPosition();
		m_rotation = GetRotation();
	}
}