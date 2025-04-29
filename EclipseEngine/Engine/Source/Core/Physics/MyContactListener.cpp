#include "Core/Physics/MyContactListener.hpp"
#include "Core/Physics/PhysicsSystem.hpp"

void MyContactListener::Init(Core::PhysicsSystem* _physicSystem)
{
	m_physicsSystem = _physicSystem;
}

void MyContactListener::OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
	inManifold;
	ioSettings;
	m_physicsSystem->CallOnCollisionEnter(inBody1, inBody2);
}

void MyContactListener::OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
	inManifold;
	ioSettings;
	m_physicsSystem->CallOnCollisionStay(inBody1, inBody2);
}

void MyContactListener::OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair)
{
	m_physicsSystem->CallOnCollisionExit(inSubShapePair.GetBody1ID(), inSubShapePair.GetBody2ID());
}