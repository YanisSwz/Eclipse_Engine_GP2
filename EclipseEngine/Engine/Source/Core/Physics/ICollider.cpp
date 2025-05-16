#include "Core/Physics/ICollider.hpp"
#include "GameObject.hpp"

namespace Core
{
	void ICollider::SetActive(bool _activate)
	{
		m_active = _activate;
		if (m_active)
		{
			AddBodyToPhysicsEngine();
			if (m_gameObject != nullptr)
			{
				SetPosition(m_gameObject->transform->GetPosition() + m_gameObject->transform->GetRotation().Rotate(GetOffsetPos()));
				SetRotation(m_gameObject->transform->GetRotation());
			}
		}
		else
		{
			RemoveBodyToPhysicsEngine();
		}
	}

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
		if (b_isBodyDestroyed)
			return;

		if (m_bodyInterface)
		{
			if (!m_bodyInterface->IsAdded(m_bodyID))
				m_bodyInterface->AddBody(m_bodyID, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
		}
	}

	void ICollider::RemoveBodyToPhysicsEngine()
	{
		if (b_isBodyDestroyed)
			return;

		if (m_bodyInterface)
		{
			if (m_bodyInterface->IsAdded(m_bodyID))
				m_bodyInterface->RemoveBody(m_bodyID);
		}
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
		m_bodyInterface->SetRotation(m_bodyID, JPH::Quat(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w), isActivate);
	}

	void ICollider::SetPosRot(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ)
	{
		m_rotation = Math::Quat::QuaternionEuler(_rotX, _rotY, _rotZ);
		m_position = { _posX, _posY, _posZ };
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPositionAndRotation(m_bodyID, { m_position.x, m_position.y, m_position.z }, JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }), isActivate);
	}

	void ICollider::SetPosRot(Math::Vec3 _position, Math::Vec3 _rotation)
	{
		m_rotation = Math::Quat::QuaternionEuler(_rotation.x, _rotation.y, _rotation.z);
		m_position = _position;
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPositionAndRotation(m_bodyID, { m_position.x, m_position.y, m_position.z }, JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }), isActivate);
	}

	void ICollider::SetPosRot(Math::Vec3 _position, Math::Quat _rotation)
	{
		m_rotation = _rotation;
		m_position = _position;
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPositionAndRotation(m_bodyID, { m_position.x, m_position.y, m_position.z }, JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }), isActivate);
	}

	void ICollider::SetPosRotScale(float _posX, float _posY, float _posZ, float _rotX, float _rotY, float _rotZ, float _scaleX, float _scaleY, float _scaleZ)
	{
		SetPosRot({ _posX, _posY, _posZ }, Math::Vec3{ _rotX, _rotY, _rotZ });
		Scale({ _scaleX, _scaleY, _scaleZ });
	}

	void ICollider::SetPosRotScale(Math::Vec3 _position, Math::Vec3 _rotation, Math::Vec3 _scale)
	{

		SetPosRot({ _position.x, _position.y, _position.z }, Math::Vec3{ _rotation.x, _rotation.y, _rotation.z });
		Scale({ _scale.x, _scale.y, _scale.z });
	}

	void ICollider::SetOffsetPos(float _offsetPosX, float _offsetPosY, float _offsetPosZ)
	{
		m_rotation = GetRotation();
		m_position -= m_rotation.Rotate(m_offsetPos);
		m_offsetPos = { _offsetPosX, _offsetPosY, _offsetPosZ };
		m_position += m_rotation.Rotate(m_offsetPos);
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPosition(m_bodyID, { m_position.x, m_position.y, m_position.z }, isActivate);
	}

	void ICollider::SetOffsetPos(Math::Vec3 _offsetPos)
	{
		m_rotation = GetRotation();
		m_position -= m_rotation.Rotate(m_offsetPos);
		m_offsetPos = _offsetPos;
		m_position += m_rotation.Rotate(m_offsetPos);
		JPH::EActivation isActivate = b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate;
		m_bodyInterface->SetPosition(m_bodyID, { m_position.x, m_position.y, m_position.z }, isActivate);
	}

	void ICollider::SetVelocity(Math::Vec3 _velocity)
	{
		m_bodyInterface->SetLinearVelocity(m_bodyID, {_velocity.x, _velocity.y, _velocity.z});
	}

	Math::Vec3 ICollider::GetPosition() const
	{
		JPH::Vec3 pos = m_bodyInterface->GetPosition(m_bodyID);
		return { pos.GetX(), pos.GetY(), pos.GetZ() };
	}

	Math::Vec3 ICollider::GetOffsetPos() const
	{
		return m_offsetPos;
	}

	Math::Vec3 ICollider::GetOffsetPosRotated() const
	{
		JPH::Quat jphRot = m_bodyInterface->GetRotation(m_bodyID);
		Math::Quat rot{ jphRot.GetW(), jphRot.GetX(), jphRot.GetY(), jphRot.GetZ() };
		return rot.Rotate(m_offsetPos);
	}

	Math::Quat ICollider::GetRotation() const
	{
		JPH::Quat rot = m_bodyInterface->GetRotation(m_bodyID);
		return { rot.GetW(), rot.GetX(), rot.GetY(), rot.GetZ() };
	}

	Math::Vec3 ICollider::GetScale() const
	{
		return m_scale;
	}

	float ICollider::GetMass() const
	{
		return m_mass;
	}

	bool ICollider::GetIsDynamic() const
	{
		return b_isDynamic;
	}

	JPH::BodyID ICollider::GetBodyID() const
	{
		return m_bodyID;
	}

	Math::Vec3 ICollider::GetVelocity() const 
	{
		JPH::Vec3 velocity = m_bodyInterface->GetLinearVelocity(m_bodyID);
		return { velocity.GetX(), velocity.GetY(), velocity.GetZ() };
	}

	void ICollider::Destroy()
	{
		m_active = false;
		m_destroyed = true;
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