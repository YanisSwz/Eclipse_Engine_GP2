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

	Math::Vec3 ICollider::GetPosition() const
	{
		JPH::Vec3 pos = m_bodyInterface->GetPosition(m_bodyID);
		return { pos.GetX(), pos.GetY(), pos.GetZ() };
	}
}