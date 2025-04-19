#include "Physics/MeshCollider.hpp"

// Jolt Includes
#include <Jolt/Jolt.h>
#include <Jolt/Physics/EActivation.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
using namespace JPH::literals;

#include "Resource/ResourceManager.hpp"
#include "Resource/Mesh.hpp"

namespace Core
{
	MeshCollider::MeshCollider()
	{
	}

	MeshCollider::MeshCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic, Math::Vec3 _size, Math::Vec3 _pos, Math::Vec3 _rot)
	{
		m_bodyInterface = _bodyInterface;
		b_isDynamic = _isDynamic;
		m_position = _pos;
		m_rotation = _rot;
		m_scale = _size;

		m_vertexList.clear();
		m_indexTriangleList.clear();

		Resource::Mesh* mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("VikingRoom.obj");
		std::vector<Math::Vec3> verticesPosition = mesh->GetVerticesPosition();
		std::vector<uint32_t> verticesIndex = mesh->GetVerticesIndex();

		Math::Vec3 pos;
		for (int i = 0; i < verticesPosition.size(); ++i)
		{
			pos = verticesPosition[i];
			m_vertexList.push_back({ pos.x, pos.y, pos.z });
		}
		
		for (int i = 0; i < verticesIndex.size(); i += 3)
			m_indexTriangleList.push_back({ verticesIndex[i], verticesIndex[i + 1], verticesIndex[i + 2] });

		JPH::MeshShapeSettings shapeSettings(m_vertexList, m_indexTriangleList);
		shapeSettings.SetEmbedded();
		JPH::ShapeSettings::ShapeResult shapeResult = shapeSettings.Create();

		if (!shapeResult.IsValid())
			return;

		JPH::ShapeRefC shape = shapeResult.Get();
		JPH::BodyCreationSettings bodySettings(
			shape,
			JPH::RVec3(m_position.x, m_position.y, m_position.z),
			JPH::Quat::sEulerAngles({ m_rotation.x, m_rotation.y, m_rotation.z }),
			b_isDynamic ? JPH::EMotionType::Dynamic : JPH::EMotionType::Static,
			b_isDynamic ? JPH::Layers::MOVING : JPH::Layers::NON_MOVING);

		bodySettings.mAllowDynamicOrKinematic = true;
		bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::CalculateInertia;
		bodySettings.mMassPropertiesOverride.mMass = 1.f;

		JPH::Body* body = m_bodyInterface->CreateBody(bodySettings);
		m_bodyID = body->GetID();
		m_bodyInterface->AddBody(m_bodyID, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
	}

	MeshCollider::~MeshCollider()
	{
		Delete();
	}

	Math::Quat MeshCollider::GetRotation() const
	{
		JPH::Quat quat = m_bodyInterface->GetRotation(m_bodyID);
		return { quat.GetW(), quat.GetX(), quat.GetY(), quat.GetZ()};
	}

	void MeshCollider::Delete()
	{
		if (m_bodyInterface)
		{
			if (m_bodyInterface->IsAdded(m_bodyID))
				m_bodyInterface->RemoveBody(m_bodyID);
			if (m_bodyID.IsInvalid())
				m_bodyInterface->DestroyBody(m_bodyID);
		}
	}
}