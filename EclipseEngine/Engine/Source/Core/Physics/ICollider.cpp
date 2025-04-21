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
		m_bodyInterface->SetRotation(m_bodyID, JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }), isActivate);
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

	void ICollider::Delete()
	{
		if (m_bodyInterface)
		{
			if (m_bodyInterface->IsAdded(m_bodyID))
				m_bodyInterface->RemoveBody(m_bodyID);
			if (m_bodyID.IsInvalid())
				m_bodyInterface->DestroyBody(m_bodyID);
		}
	}

	void ICollider::UpdateData()
	{
		m_position = GetPosition();
		m_rotation = GetRotation();
	}
}