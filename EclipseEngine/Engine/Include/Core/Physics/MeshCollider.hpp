#pragma once
#include "ICollider.hpp"
#include "ProjectExports.hpp"

#include <Jolt/Jolt.h>
#include <Jolt/Math/Float3.h>
#include <Jolt/Geometry/IndexedTriangle.h>

namespace Core
{
	class MeshCollider : public ICollider
	{
	public:
		ECLIPSE_ENGINE MeshCollider();
		ECLIPSE_ENGINE MeshCollider(JPH::BodyInterface* _bodyInterface, bool _isDynamic = false, float _mass = 1.f, Math::Vec3 _size = { 1.f, 1.f, 1.f }, Math::Vec3 _pos = { 0.f, 0.f, 0.f }, Math::Vec3 _rot = { 0.f, 0.f, 0.f }, GameObject* _myGameObject = nullptr);
		ECLIPSE_ENGINE ~MeshCollider() override;
		
		ECLIPSE_ENGINE void SetMass(float _mass) override;

	private:
		Math::Vec3 m_scale = { 0.f, 0.f, 0.f };

		JPH::VertexList m_vertexList;
		JPH::IndexedTriangleList m_indexTriangleList;
	};
}