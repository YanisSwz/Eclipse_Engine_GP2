#include "Physics/CapsuleCollider.hpp"
#include "GameObject.hpp"

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

	CapsuleCollider::CapsuleCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic, float _mass, 
		Math::Vec3 _scale, Math::Vec3 _pos, Math::Vec3 _rot, GameObject* _myGameObject, 
		Math::Vec3 _linearVelocity, Math::Vec3 _angularVelocity)
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
			JPH::Quat( m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w ),
			b_isDynamic ? JPH::EMotionType::Dynamic : JPH::EMotionType::Static,
			b_isDynamic ? JPH::Layers::MOVING : JPH::Layers::NON_MOVING);

		bodySettings.mAllowDynamicOrKinematic = true;
		bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::MassAndInertiaProvided;
		bodySettings.mMassPropertiesOverride.mMass = m_mass;
		bodySettings.mAllowSleeping = false;

		JPH::Body* body = m_bodyInterface->CreateBody(bodySettings);
		m_bodyID = body->GetID();
		m_bodyInterface->AddBody(m_bodyID, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
		m_bodyInterface->SetLinearVelocity(m_bodyID, { _linearVelocity.x, _linearVelocity.y, _linearVelocity.z });
		m_bodyInterface->SetAngularVelocity(m_bodyID, { _angularVelocity.x, _angularVelocity.y, _angularVelocity.z });
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

		if (_scaleX != _scaleZ)
			_scaleZ = _scaleX;

		m_scale = { _scaleX, _scaleY, _scaleZ };
		Recreate();
	}

	void CapsuleCollider::Scale(Math::Vec3 _scale)
	{
		if (_scale.x <= 0.f || _scale.y <= 0.f || _scale.z <= 0.f)
			return;

		if (_scale.x != _scale.z)
			_scale.z = _scale.x;

		m_scale = _scale;
		Recreate();
	}

	void CapsuleCollider::Recreate()
	{
		UpdateData();

		Core::GameObject* gameObject = m_gameObject;
		JPH::BodyInterface* bodyInterface = m_bodyInterface;
		bool isDynamic = b_isDynamic;
		float mass = m_mass;
		Math::Vec3 scale = m_scale;
		Math::Vec3 position = m_position;
		Math::Vec3 rotationEuler = m_rotation.GetEulerAnglesDegZYX();
		JPH::Vec3 jphVelocity = m_bodyInterface->GetLinearVelocity(m_bodyID);
		Math::Vec3 myVelocity{ jphVelocity.GetX(), jphVelocity.GetY(), jphVelocity.GetZ()};
		JPH::Vec3 jphAngularVelocity = m_bodyInterface->GetAngularVelocity(m_bodyID);
		Math::Vec3 myAngularVelocity{ jphVelocity.GetX(), jphVelocity.GetY(), jphVelocity.GetZ() };

		this->~CapsuleCollider();
		new (this) CapsuleCollider(bodyInterface, isDynamic, mass, scale, position, rotationEuler, gameObject,
			myVelocity, myAngularVelocity);
	}

	void CapsuleCollider::Serialize(json& _j)
	{
		Math::Vec3 offsetPosition = GetOffsetPos();
		Math::Vec3 scale = GetScale();
		Math::Quat rotation = GetRotation();

		_j["CapsuleCollider"] = json{
			{"IsActive", GetGameObject()->IsActive()},
			{"IsDynamic", GetIsDynamic()},
			{"OffsetPosition", {offsetPosition.x, offsetPosition.y, offsetPosition.z}},
			{"Scale", {scale.x, scale.y, scale.z}},
			{"Rotation", {rotation.w, rotation.x, rotation.y, rotation.z}},
			{"Mass", GetMass()}
		};
	}

	void CapsuleCollider::Deserialize(const json& _j)
	{
		bool bIsActive;
		bool bIsDynamic;
		float offsetPosition[3];
		float scale[3];
		float rotation[4];
		float mass;

		_j.at("IsActive").get_to(bIsActive);
		_j.at("IsDynamic").get_to(bIsDynamic);
		_j.at("OffsetPosition").get_to(offsetPosition);
		_j.at("Scale").get_to(scale);
		_j.at("Rotation").get_to(rotation);
		_j.at("Mass").get_to(mass);

		SetDynamic(bIsDynamic);
		SetOffsetPos(Math::Vec3(offsetPosition[0], offsetPosition[1], offsetPosition[2]));
		Scale(Math::Vec3(scale[0], scale[1], scale[2]));
		SetRotation(Math::Quat(rotation[0], rotation[1], rotation[2], rotation[3]));
		SetMass(mass);
		SetActive(bIsActive);
	}
}