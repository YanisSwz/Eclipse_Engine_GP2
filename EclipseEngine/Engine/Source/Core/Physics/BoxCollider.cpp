#include "Physics/BoxCollider.hpp"

// Jolt Includes
#include <Jolt/Jolt.h>
#include <Jolt/Physics/EActivation.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Math/Math.h>
using namespace JPH::literals;

#include "Logging/Logger.hpp"

namespace Core
{
	meta::factory<BoxCollider> BoxCollider::factory = meta::reflect<BoxCollider>(m_hash("BoxCollider"))
		.data<&BoxCollider::SetActive, &BoxCollider::IsActive>(m_hash("IsActive"))
		.data<&BoxCollider::SetDynamic, &BoxCollider::GetIsDynamic>(m_hash("IsDynamic"))
		.data<&BoxCollider::SetMass, &BoxCollider::GetMass>(m_hash("Mass"));
		//.func<&BoxCollider::GetOffsetPos>(m_hash("GetPositionOffset"))
		//.func<&BoxCollider::GetScale>(m_hash("GetScale"))
		//.func<&BoxCollider::SetOffsetPos>(m_hash("SetPositionOffset"));
		//.func<&BoxCollider::Scale>(m_hash("SetScale"));

	BoxCollider::BoxCollider()
	{
	}

	BoxCollider::BoxCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic, float _mass, Math::Vec3 _size, Math::Vec3 _pos, Math::Vec3 _rot, GameObject* _myGameObject)
	{
		b_isBodyDestroyed = false;
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
		bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::MassAndInertiaProvided;
		bodySettings.mMassPropertiesOverride.mMass = m_mass;
		bodySettings.mAllowSleeping = false;

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

	void BoxCollider::Scale(float _scaleX, float _scaleY, float _scaleZ)
	{
		if (_scaleX <= 0.f || _scaleY <= 0.f || _scaleZ <= 0.f)
			return;

		m_scale = { _scaleX, _scaleY, _scaleZ };
		Recreate();

	}

	void BoxCollider::Scale(Math::Vec3 _scale)
	{
		if (_scale.x <= 0.f || _scale.y <= 0.f || _scale.z <= 0.f)
			return;

		m_scale = _scale;
		Recreate();

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