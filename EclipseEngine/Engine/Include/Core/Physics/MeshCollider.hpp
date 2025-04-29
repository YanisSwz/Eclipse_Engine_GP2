#pragma once
#include "ICollider.hpp"
#include "ProjectExports.hpp"
#include "meta/factory.hpp"
#include <string>
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
		static meta::factory<MeshCollider> factory;

		ECLIPSE_ENGINE MeshCollider();
		ECLIPSE_ENGINE MeshCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic = false, float _mass = 1.f, Math::Vec3 _size = { 1.f, 1.f, 1.f }, Math::Vec3 _pos = { 0.f, 0.f, 0.f }, Math::Vec3 _rot = { 0.f, 0.f, 0.f }, GameObject* _myGameObject = nullptr, JPH::VertexList _vertexList = JPH::VertexList(), JPH::IndexedTriangleList _indexTriangleList = JPH::IndexedTriangleList());
		ECLIPSE_ENGINE ~MeshCollider() override;
		
		ECLIPSE_ENGINE void SetMesh(const char* _meshName);
		ECLIPSE_ENGINE void SetMesh(Resource::Mesh* _mesh);
		ECLIPSE_ENGINE void SetMeshScale(const char* _meshName, Math::Vec3 _scale);
		ECLIPSE_ENGINE void SetMeshScale(Resource::Mesh* _mesh, Math::Vec3 _scale);
		ECLIPSE_ENGINE void SetMass(float _mass) override;
		ECLIPSE_ENGINE void Scale(float _scaleX, float _scaleY, float _scaleZ) override;
		ECLIPSE_ENGINE void Scale(Math::Vec3 _scale) override;

	private:
		inline static std::hash<std::string_view> m_hash{};

		JPH::VertexList m_vertexList;
		JPH::IndexedTriangleList m_indexTriangleList;
		const char* m_defaultMesh = "Cube.obj";
		Resource::Mesh* m_currentMesh = nullptr;

		void SetDefaultMesh();
		void Recreate() override;
	};
}