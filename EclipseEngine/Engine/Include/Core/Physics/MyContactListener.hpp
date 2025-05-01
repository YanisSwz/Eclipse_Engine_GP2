#pragma once

// Jolt Include
#include <Jolt/Jolt.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

namespace Core
{
	class PhysicsSystem;
}

// An example contact listener
class MyContactListener : public JPH::ContactListener
{
public:
	MyContactListener() = default;
	~MyContactListener() = default;

	void Init(Core::PhysicsSystem* _physicSystem);

	virtual void OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;
	virtual void OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;
	virtual void OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override;

private:
	Core::PhysicsSystem* m_physicsSystem = nullptr;
};