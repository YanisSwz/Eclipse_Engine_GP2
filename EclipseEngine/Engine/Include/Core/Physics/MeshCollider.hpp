#pragma once
#include "ICollider.hpp"
#include "ProjectExports.hpp"

#include <Jolt/Jolt.h>
#include <Jolt/Math/Float3.h>
#include <Jolt/Geometry/IndexedTriangle.h>

namespace Resource
{
	class Mesh;
}

namespace Core
{
	class MeshCollider : public ICollider
	{
	public:
		ECLIPSE_ENGINE MeshCollider();
		ECLIPSE_ENGINE MeshCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic = false, float _mass = 1.f, Math::Vec3 _size = { 1.f, 1.f, 1.f }, Math::Vec3 _pos = { 0.f, 0.f, 0.f }, Math::Vec3 _rot = { 0.f, 0.f, 0.f }, GameObject* _myGameObject = nullptr, JPH::VertexList _vertexList = JPH::VertexList(), JPH::IndexedTriangleList _indexTriangleList = JPH::IndexedTriangleList());
		ECLIPSE_ENGINE ~MeshCollider() override;
		
		ECLIPSE_ENGINE void SetMesh(const char* _meshName);
		ECLIPSE_ENGINE void SetMesh(Resource::Mesh* _mesh);
		ECLIPSE_ENGINE void SetMass(float _mass) override;

	private:
		Math::Vec3 m_scale = { 0.f, 0.f, 0.f };

		bool b_isMeshChanged = false;
		JPH::VertexList m_vertexList;
		JPH::IndexedTriangleList m_indexTriangleList;
		const char* m_defaultMesh = "Cube.obj";

		void SetDefaultMesh();
	};
}