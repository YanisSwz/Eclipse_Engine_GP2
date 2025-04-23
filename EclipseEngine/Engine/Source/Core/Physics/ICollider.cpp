#include "Core/Physics/ICollider.hpp"

namespace Core
{
	void ICollider::SetDynamic(bool _isDynamic)
	{
		if (b_isDynamic == _isDynamic)
			return;

		b_isDynamic = _isDynamic;

		JPH::EMotionType motionType = b_isDynamic ? JPH::EMotionType::Dynamic : JPH::EMotionType::Static;
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		JPH::ObjectLayer objectLayer = b_isDynamic ? JPH::Layers::MOVING : JPH::Layers::NON_MOVING;
		m_bodyInterface->SetMotionType(m_bodyID, motionType, isActivate);
		m_bodyInterface->SetObjectLayer(m_bodyID, objectLayer);
	}

	void ICollider::AddForce(float _forceX, float _forceY, float _forceZ)
	{
		m_bodyInterface->AddForce(m_bodyID, { _forceX, _forceY, _forceZ }, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
	}

	void ICollider::AddForce(Math::Vec3 _force)
	{
		m_bodyInterface->AddForce(m_bodyID, { _force.x, _force.y, _force.z }, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
	}

	void ICollider::AddForce(Math::Vec3 _dir, float _force)
	{
		m_bodyInterface->AddForce(m_bodyID, { _dir.x * _force, _dir.y * _force, _dir.z * _force }, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
	}

	void ICollider::AddImpulse(float _impulseX, float _impulseY, float _impulseZ)
	{
		m_bodyInterface->AddImpulse(m_bodyID, { _impulseX, _impulseY, _impulseZ });
	}

	void ICollider::AddImpulse(Math::Vec3 _impulse)
	{
		m_bodyInterface->AddImpulse(m_bodyID, { _impulse.x, _impulse.y, _impulse.z });
	}

	void ICollider::AddImpulse(Math::Vec3 _dir, float _impulse)
	{
		m_bodyInterface->AddImpulse(m_bodyID, { _dir.x * _impulse, _dir.y * _impulse, _dir.z * _impulse });
	}

	void ICollider::AddBodyToPhysicsEngine()
	{
		m_bodyInterface->AddBody(m_bodyID, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
	}

	void ICollider::RemoveBodyToPhysicsEngine()
	{
		m_bodyInterface->RemoveBody(m_bodyID);
	}

	void ICollider::SetPosition(float _posX, float _posY, float _posZ)
	{
		m_position = { _posX, _posY, _posZ };
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPosition(m_bodyID, { m_position.x, m_position.y, m_position.z }, isActivate);
	}

	void ICollider::SetPosition(Math::Vec3 _position)
	{
		m_position = _position;
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPosition(m_bodyID, { m_position.x, m_position.y, m_position.z }, isActivate);
	}

	void ICollider::SetRotation(float _rotX, float _rotY, float _rotZ)
	{
		m_rotation = Math::Quat::QuaternionEuler(_rotX, _rotY, _rotZ);
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetRotation(m_bodyID, JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }), isActivate);
	}

	void ICollider::SetRotation(Math::Vec3 _rotation)
	{
		m_rotation = Math::Quat::QuaternionEuler(_rotation.x, _rotation.y, _rotation.z);
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetRotation(m_bodyID, JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }), isActivate);
	}

	void ICollider::SetRotation(Math::Quat _rotation)
	{
		m_rotation = _rotation;
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetRotation(m_bodyID, JPH::Quat( m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w), isActivate);
	}

	void ICollider::SetPosRot(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ)
	{
		m_position = { _posX, _posY, _posZ };
		m_rotation = Math::Quat::QuaternionEuler(_rotX, _rotY, _rotZ);
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPositionAndRotation(m_bodyID, { m_position.x, m_position.y, m_position.z }, JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }), isActivate);
	}

	void ICollider::SetPosRot(Math::Vec3 _position, Math::Vec3 _rotation)
	{
		m_position = _position;
		m_rotation = Math::Quat::QuaternionEuler(_rotation.x, _rotation.y, _rotation.z);
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPositionAndRotation(m_bodyID, { m_position.x, m_position.y, m_position.z }, JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }), isActivate);
	}

	void ICollider::SetPosRot(Math::Vec3 _position, Math::Quat _rotation)
	{
		m_position = _position;
		m_rotation = _rotation;
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPositionAndRotation(m_bodyID, { m_position.x, m_position.y, m_position.z }, JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }), isActivate);
	}

	Math::Vec3 ICollider::GetPosition() const
	{
		JPH::Vec3 pos = m_bodyInterface->GetPosition(m_bodyID);
		return { pos.GetX(), pos.GetY(), pos.GetZ() };
	}

	Math::Quat ICollider::GetRotation() const
	{
		JPH::Quat rot = m_bodyInterface->GetRotation(m_bodyID);
		return { rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ() };
	}

	float ICollider::GetMass() const
	{
		return m_mass;
	}

	bool ICollider::GetIsDynamic() const
	{
		return b_isDynamic;
	}
	
	void ICollider::Destroy()
	{
		active = false;
		destroyed = true;
		Delete();
	}

	void ICollider::Delete()
	{
		if (m_bodyInterface && !b_isBodyDestroyed)
		{
			if (m_bodyInterface->IsAdded(m_bodyID))
				m_bodyInterface->RemoveBody(m_bodyID);
			if (m_bodyID.IsInvalid())
				m_bodyInterface->DestroyBody(m_bodyID);
		}
		b_isBodyDestroyed = true;
		m_gameObject = nullptr;
	}

	void ICollider::UpdateData()
	{
		m_position = GetPosition();
		m_rotation = GetRotation();
	}
}