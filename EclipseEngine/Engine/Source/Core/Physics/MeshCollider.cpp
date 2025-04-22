#include "Physics/MeshCollider.hpp"
#include "Logger.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Mesh.hpp"

// Jolt Includes
#include <Jolt/Jolt.h>
#include <Jolt/Physics/EActivation.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
using namespace JPH::literals;

namespace Core
{
	MeshCollider::MeshCollider()
	{
	}

	MeshCollider::MeshCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic, float _mass, Math::Vec3 _size, Math::Vec3 _pos, Math::Vec3 _rot, GameObject* _myGameObject, JPH::VertexList _vertexList, JPH::IndexedTriangleList _indexTriangleList)
	{
		m_bodyInterface = _bodyInterface;
		b_isDynamic = _isDynamic;
		m_mass = _mass;
		m_position = _pos;
		m_rotation = Math::Quat::QuaternionEuler(_rot.x, _rot.y, _rot.z);
		m_scale = _size;
		m_gameObject = _myGameObject;
		m_vertexList = _vertexList;
		m_indexTriangleList = _indexTriangleList;


		if (m_vertexList.size() == 0)
			SetDefaultMesh();

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
		bodySettings.mMassPropertiesOverride.mMass = m_mass;

		JPH::Body* body = m_bodyInterface->CreateBody(bodySettings);
		m_bodyID = body->GetID();
		m_bodyInterface->AddBody(m_bodyID, b_isDynamic ? JPH::EActivation::Activate : JPH::EActivation::DontActivate);
	}

	MeshCollider::~MeshCollider()
	{
		Delete();
	}

	void MeshCollider::SetMesh(const char* _meshName)
	{
		Resource::Mesh* mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(_meshName);
		SetMeshScale(mesh, { 1.f, 1.f, 1.f });
	}

	void MeshCollider::SetMesh(Resource::Mesh* _mesh)
	{
		SetMeshScale(_mesh, { 1.f, 1.f, 1.f });
	}

	void MeshCollider::SetMeshScale(const char* _meshName, Math::Vec3 _scale)
	{
		Resource::Mesh* mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(_meshName);
		SetMeshScale(mesh, _scale);
	}

	void MeshCollider::SetMeshScale(Resource::Mesh* _mesh, Math::Vec3 _scale)
	{
		if (!_mesh)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "Mesh not found for the mesh collider! The previous mesh collider will be used!");
			return;
		}

		m_currentMesh = _mesh;

		m_vertexList.clear();
		m_indexTriangleList.clear();
		std::vector<Math::Vec3> verticesPosition = _mesh->GetVerticesPosition();
		std::vector<uint32_t> verticesIndex = _mesh->GetVerticesIndex();

		JPH::VertexList vertexList;
		JPH::IndexedTriangleList indexTriangleList;

		Math::Vec3 pos;
		for (int i = 0; i < verticesPosition.size(); ++i)
		{
			pos = verticesPosition[i] * m_scale;
			vertexList.push_back({ pos.x * _scale.x, pos.y * _scale.y, pos.z * _scale.z });
		}

		for (int i = 0; i < verticesIndex.size(); i += 3)
			indexTriangleList.push_back({ verticesIndex[i], verticesIndex[i + 1], verticesIndex[i + 2] });

		Recreate();
	}

	void MeshCollider::SetMass(float _mass)
	{
		m_mass = _mass;
		Recreate();
	}

	void MeshCollider::SetDefaultMesh()
	{
		Resource::Mesh* mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(m_defaultMesh);
		if (!mesh)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "Mesh not found for the mesh collider! The previous mesh collider will be used!");
			return;
		}

		m_vertexList.clear();
		m_indexTriangleList.clear();
		std::vector<Math::Vec3> verticesPosition = mesh->GetVerticesPosition();
		std::vector<uint32_t> verticesIndex = mesh->GetVerticesIndex();

		Math::Vec3 pos;
		for (int i = 0; i < verticesPosition.size(); ++i)
		{
			pos = verticesPosition[i] * m_scale;
			m_vertexList.push_back({ pos.x, pos.y, pos.z });
		}

		for (int i = 0; i < verticesIndex.size(); i += 3)
			m_indexTriangleList.push_back({ verticesIndex[i], verticesIndex[i + 1], verticesIndex[i + 2] });
	}

	void MeshCollider::Scale(Math::Vec3 _scale)
	{
		SetMeshScale(m_currentMesh, _scale);
	}

	void MeshCollider::Scale(float _scaleX, float _scaleY, float _scaleZ)
	{
		SetMeshScale(m_currentMesh, { _scaleX, _scaleY, _scaleZ });
	}

	void MeshCollider::Recreate()
	{
		Core::GameObject* gameObject = m_gameObject;
		UpdateData();
		this->~MeshCollider();
		new (this) MeshCollider(m_bodyInterface, b_isDynamic, m_mass, m_scale, m_position, m_rotation.GetEulerAnglesRadXYZ(), gameObject);
	}
}