#pragma once
#include "Physics/BoxCollider.hpp"
#include "Physics/CapsuleCollider.hpp"
#include "Physics/MeshCollider.hpp"
#include "ProjectExports.hpp"
#include <vector>

// Jolt Include
#include "Core/Physics/Layers.hpp"
#include <Jolt/Jolt.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyInterface.h>

// JoltViewer include
#include <Jolt/Core/StreamWrapper.h>
#include <Jolt/Renderer/DebugRendererRecorder.h>
#include <fstream>

/// Class that determines if two object layers can collide
class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
{
public:
	virtual bool					ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const override
	{
		switch (inObject1)
		{
		case JPH::Layers::NON_MOVING:
			return inObject2 == JPH::Layers::MOVING; // Non moving only collides with moving
		case JPH::Layers::MOVING:
			return true; // Moving collides with everything
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

// Each broadphase layer results in a separate bounding volume tree in the broad phase. You at least want to have
// a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
// You can have a 1-on-1 mapping between object layers and broadphase layers (like in this case) but if you have
// many object layers you'll be creating many broad phase trees, which is not efficient. If you want to fine tune
// your broadphase layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on the TTY.
namespace BroadPhaseLayers
{
	static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
	static constexpr JPH::BroadPhaseLayer MOVING(1);
	static constexpr JPH::uint NUM_LAYERS(2);
};

// BroadPhaseLayerInterface implementation
// This defines a mapping between object and broadphase layers.
class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
{
public:
	BPLayerInterfaceImpl()
	{
		// Create a mapping table from object to broad phase layer
		mObjectToBroadPhase[JPH::Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
		mObjectToBroadPhase[JPH::Layers::MOVING] = BroadPhaseLayers::MOVING;
	}

	virtual JPH::uint					GetNumBroadPhaseLayers() const override
	{
		return BroadPhaseLayers::NUM_LAYERS;
	}

	virtual JPH::BroadPhaseLayer			GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override
	{
		JPH_ASSERT(inLayer < JPH::Layers::NUM_LAYERS);
		return mObjectToBroadPhase[inLayer];
	}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
	virtual const char* GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override
	{
		switch ((BroadPhaseLayer::Type)inLayer)
		{
		case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:	return "NON_MOVING";
		case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:		return "MOVING";
		default:													JPH_ASSERT(false); return "INVALID";
		}
	}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

private:
	JPH::BroadPhaseLayer					mObjectToBroadPhase[JPH::Layers::NUM_LAYERS];
};

/// Class that determines if an object layer can collide with a broadphase layer
class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
	virtual bool				ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
	{
		switch (inLayer1)
		{
		case JPH::Layers::NON_MOVING:
			return inLayer2 == BroadPhaseLayers::MOVING;
		case JPH::Layers::MOVING:
			return true;
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

namespace Core
{
	class PhysicsSystem
	{
	public:
		ECLIPSE_ENGINE PhysicsSystem();
		ECLIPSE_ENGINE ~PhysicsSystem();
		ECLIPSE_ENGINE BoxCollider* AddBoxCollider();
		ECLIPSE_ENGINE CapsuleCollider* AddCapsuleCollider();
		ECLIPSE_ENGINE MeshCollider* AddMeshCollider();

		ECLIPSE_ENGINE void Update(float _deltaTime);

	private:
		static const int MAX_COLLIDER_SIZE = 1000;
		int m_currentColliderCount = 0;
		int m_currentBoxColliderCount = 0;
		BoxCollider m_boxColliders[MAX_COLLIDER_SIZE];
		int m_currentCapsuleColliderCount = 0;
		CapsuleCollider m_capsuleColliders[MAX_COLLIDER_SIZE];
		int m_currentMeshColliderCount = 0;
		MeshCollider m_meshColliders[MAX_COLLIDER_SIZE];

		// Jolt Physics Setup
		JPH::TempAllocatorImpl* m_tempAllocator; // Pre-allocating memory for the physics update
		JPH::JobSystemThreadPool* m_jobSystem = nullptr;
		JPH::PhysicsSystem m_physicsSystem;
		JPH::BodyInterface* m_bodyInterface = nullptr;
		// Create mapping table from object layer to broadphase layer
		BPLayerInterfaceImpl m_broadPhaseLayerInterface;
		// Create class that filters object vs broadphase layers
		ObjectVsBroadPhaseLayerFilterImpl m_objectVsBroadphaseLayerFilter;
		// Create class that filters object vs object layers
		ObjectLayerPairFilterImpl m_objectVsObjectLayerFilter;

		// JoltViewer
		JPH::DebugRendererRecorder* m_renderer = nullptr;
		JPH::StreamOutWrapper* m_rendererStream = nullptr;
		std::ofstream m_rendererFile;

		bool b_firstUpdate = true;
	};
}