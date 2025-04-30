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
	meta::factory<CapsuleCollider> CapsuleCollider::factory = meta::reflect<CapsuleCollider>(hash("CapsuleCollider"))
		.data<&CapsuleCollider::SetActive, &CapsuleCollider::IsActive>(hash("IsActive"))
		.data<&CapsuleCollider::SetDynamic, &CapsuleCollider::GetIsDynamic>(hash("IsDynamic"))
		.data<&CapsuleCollider::SetMass, &CapsuleCollider::GetMass>(hash("Mass"));
		//.func<&CapsuleCollider::GetOffsetPos>(hash("GetPositionOffset"))
		//.func<&CapsuleCollider::GetScale>(hash("GetScale"))
		//.func<&BoxCollider::SetOffsetPos<Math::Vec3>>(hash("SetPositionOffset"))
		//.func<&BoxCollider::Scale>(hash("SetScale"));

	CapsuleCollider::CapsuleCollider()
	{
	}

	CapsuleCollider::CapsuleCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic, float _mass, Math::Vec3 _scale, Math::Vec3 _pos, Math::Vec3 _rot, GameObject* _myGameObject)
	{
		b_isBodyDestroyed = false;
		m_bodyInterface = _bodyInterface;
		b_isDynamic = _isDynamic;
		m_mass = _mass;
		m_scale = _scale;
		m_position = _pos;
		m_rotation = Math::Quat::QuaternionEuler(_rot.x, _rot.y, _rot.z);
		m_gameObject = _myGameObject;

		JPH::CapsuleShapeSettings shapeSettings(m_scale.y * 0.5f, m_scale.x);
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
		bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::MassAndInertiaProvided;
		bodySettings.mMassPropertiesOverride.mMass = m_mass;
		bodySettings.mAllowSleeping = false;

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

	void CapsuleCollider::Scale(float _scaleX, float _scaleY, float _scaleZ)
	{
		if (_scaleX <= 0.f || _scaleY <= 0.f || _scaleZ <= 0.f)
			return;

		m_scale = { _scaleX, _scaleY, _scaleZ };
		Recreate();
	}

	void CapsuleCollider::Scale(Math::Vec3 _scale)
	{
		if (_scale.x <= 0.f || _scale.y <= 0.f || _scale.z <= 0.f)
			return;

		m_scale = _scale;
		Recreate();
	}

	void CapsuleCollider::Recreate()
	{
		Core::GameObject* gameObject = m_gameObject;
		UpdateData();
		this->~CapsuleCollider();
		new (this) CapsuleCollider(m_bodyInterface, b_isDynamic, m_mass, m_scale, m_position, m_rotation.GetEulerAnglesRadXYZ(), gameObject);
	}
}