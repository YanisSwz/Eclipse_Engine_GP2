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
	meta::factory<MeshCollider> MeshCollider::factory = meta::reflect<MeshCollider>(hash("MeshCollider"))
		.data<&MeshCollider::SetActive, &MeshCollider::IsActive>(hash("IsActive"))
		.data<&MeshCollider::SetDynamic, &MeshCollider::GetIsDynamic>(hash("IsDynamic"))
		.data<&MeshCollider::SetMass, &MeshCollider::GetMass>(hash("Mass"));
		//.func<&MeshCollider::GetOffsetPos>(hash("GetPositionOffset"))
		//.func<&MeshCollider::GetScale>(hash("GetScale"))
		//.func<&MeshCollider::SetOffsetPos<Math::Vec3>>(hash("SetPositionOffset"))
		//.func<&MeshCollider::Scale>(hash("SetScale"));

	MeshCollider::MeshCollider()
	{
	}

	MeshCollider::MeshCollider(JPH::BodyInterface* _bodyInterface, float _mass,
		Math::Vec3 _size, Math::Vec3 _pos, Math::Vec3 _rot, GameObject* _myGameObject,
		JPH::VertexList _vertexList, JPH::IndexedTriangleList _indexTriangleList,
		Math::Vec3 _linearVelocity, Math::Vec3 _angularVelocity,
		Resource::Mesh* _currMesh)
	{
		b_isBodyDestroyed = false;
		m_bodyInterface = _bodyInterface;
		b_isDynamic = false;
		m_mass = _mass;
		m_position = _pos;
		m_rotation = Math::Quat::QuaternionEuler(_rot.x, _rot.y, _rot.z);
		m_scale = _size;
		m_gameObject = _myGameObject;
		m_vertexList = _vertexList;
		m_indexTriangleList = _indexTriangleList;
		m_currentMesh = _currMesh;

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
			JPH::Quat(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w),
			JPH::EMotionType::Static,
			JPH::Layers::NON_MOVING);

		bodySettings.mAllowDynamicOrKinematic = true;
		bodySettings.mOverrideMassProperties = JPH::EOverrideMassProperties::MassAndInertiaProvided;
		bodySettings.mMassPropertiesOverride.mMass = m_mass;
		bodySettings.mAllowSleeping = false;

		JPH::Body* body = m_bodyInterface->CreateBody(bodySettings);
		m_bodyID = body->GetID();
		m_bodyInterface->AddBody(m_bodyID, JPH::EActivation::DontActivate);
		m_bodyInterface->SetLinearVelocity(m_bodyID, { _linearVelocity.x, _linearVelocity.y, _linearVelocity.z });
		m_bodyInterface->SetAngularVelocity(m_bodyID, { _angularVelocity.x, _angularVelocity.y, _angularVelocity.z });
	}

	MeshCollider::~MeshCollider()
	{
		Delete();
	}

	void MeshCollider::SetDynamic(bool _isDynamic)
	{
		// Force Mesh Collider to be Static
		b_isDynamic = false;
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
		m_scale = _scale;

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
			m_vertexList.push_back({ pos.x * _scale.x, pos.y * _scale.y, pos.z * _scale.z });
		}

		for (int i = 0; i < verticesIndex.size(); i += 3)
			m_indexTriangleList.push_back({ verticesIndex[i], verticesIndex[i + 1], verticesIndex[i + 2] });

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

	void MeshCollider::Scale(float _scaleX, float _scaleY, float _scaleZ)
	{
		if (_scaleX <= 0.f || _scaleY <= 0.f || _scaleZ <= 0.f)
			return;

		m_scale = { _scaleX, _scaleY, _scaleZ };
		Recreate();
	}

	void MeshCollider::Scale(Math::Vec3 _scale)
	{
		if (_scale.x <= 0.f || _scale.y <= 0.f || _scale.z <= 0.f)
			return;

		m_scale = _scale;
		Recreate();
	}

	std::string MeshCollider::GetMeshName() const
	{ 
		if (m_currentMesh) 
			return m_currentMesh->name; 
		else 
			return ""; 
	}

	void MeshCollider::Recreate()
	{
		UpdateData();

		Core::GameObject* gameObject = m_gameObject;
		JPH::BodyInterface* bodyInterface = m_bodyInterface;
		bool isDynamic = b_isDynamic;
		float mass = m_mass;
		Resource::Mesh* currMesh = m_currentMesh;
		Math::Vec3 scale = m_scale;
		Math::Vec3 position = m_position;
		Math::Vec3 rotationEuler = m_rotation.GetEulerAnglesDegXYZ();
		JPH::Vec3 jphVelocity = m_bodyInterface->GetLinearVelocity(m_bodyID);
		Math::Vec3 myVelocity{ jphVelocity.GetX(), jphVelocity.GetY(), jphVelocity.GetZ() };
		JPH::Vec3 jphAngularVelocity = m_bodyInterface->GetAngularVelocity(m_bodyID);
		Math::Vec3 myAngularVelocity{ jphVelocity.GetX(), jphVelocity.GetY(), jphVelocity.GetZ() };
		JPH::VertexList vertexList = m_vertexList;
		JPH::IndexedTriangleList indexTriangleList = m_indexTriangleList;

		this->~MeshCollider();
		new (this) MeshCollider(bodyInterface, mass, scale, position, rotationEuler,
			gameObject, vertexList, indexTriangleList, myVelocity, myAngularVelocity, currMesh);
	}

	void MeshCollider::Serialize(json& _j)
	{
		Math::Vec3 position = GetPosition();
		Math::Vec3 offsetPosition = GetOffsetPos();
		Math::Vec3 scale = GetScale();
		Math::Quat rotation = GetRotation();

		_j = json{
			{"IsActive", IsActive()},
			{"IsDynamic", GetIsDynamic()},
			{"Position", {position.x, position.y, position.z}},
			{"OffsetPosition", {offsetPosition.x, offsetPosition.y, offsetPosition.z}},
			{"Scale", {scale.x, scale.y, scale.z}},
			{"Rotation", {rotation.w, rotation.x, rotation.y, rotation.z}},
			{"Mass", GetMass()},
			{"Mesh", GetMeshName()}
		};
	}

	void MeshCollider::Deserialize(const json& _j)
	{
		bool bIsActive;

		_j.at("IsActive").get_to(bIsActive);

		SetActive(bIsActive);
	}
}