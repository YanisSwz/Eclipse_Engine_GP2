#include "Physics/PhysicsSystem.hpp"
#include "Logging/Logger.hpp"

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
// Disable common warnings triggered by Jolt, you can use JPH_SUPPRESS_WARNING_PUSH / JPH_SUPPRESS_WARNING_POP to store and restore the warning state
JPH_SUPPRESS_WARNINGS

#include <cstdarg>
#include <thread>

static void TraceImpl(const char* inFMT, ...)
{
	// Format the message
	va_list list;
	va_start(list, inFMT);
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), inFMT, list);
	va_end(list);

	Logging::Logger::Get()->Log(Logging::PRIORITY::INFO, buffer);
}

namespace Core
{
	PhysicsSystem::PhysicsSystem()
	{
		JPH::RegisterDefaultAllocator();
		
		JPH::Trace = TraceImpl;

		JPH::Factory::sInstance = new JPH::Factory();

		JPH::RegisterTypes();
		m_tempAllocator = new JPH::TempAllocatorImpl{ 10 * 1024 * 1024 };

		m_jobSystem = new JPH::JobSystemThreadPool( JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1 );

		const JPH::uint cMaxBodies = MAX_COLLIDER_SIZE;
		// This determines how many mutexes to allocate to protect rigid bodies from concurrent access. Set it to 0 for the default settings.
		const JPH::uint cNumBodyMutexes = 0;
		const JPH::uint cMaxBodyPairs = MAX_COLLIDER_SIZE;
		const JPH::uint cMaxContactConstraints = MAX_COLLIDER_SIZE;

		// Now we can create the actual physics system.
		m_physicsSystem.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, m_broadPhaseLayerInterface, m_objectVsBroadphaseLayerFilter, m_objectVsObjectLayerFilter);

		m_bodyInterface = &m_physicsSystem.GetBodyInterface();

		m_rendererFile.open("testScene.jor", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
		m_rendererStream = new JPH::StreamOutWrapper(m_rendererFile);
		m_renderer = new JPH::DebugRendererRecorder(*m_rendererStream);
	}

	PhysicsSystem::~PhysicsSystem()
	{
		JPH::UnregisterTypes();
		delete JPH::Factory::sInstance;
		JPH::Factory::sInstance = nullptr;

		delete m_jobSystem;
		delete m_tempAllocator;
		delete m_renderer;
		delete m_rendererStream;
		m_rendererFile.close();
	}

	BoxCollider* PhysicsSystem::AddBoxCollider(bool _isDynamic, Math::Vec3 _size, Math::Vec3 _pos, Math::Vec3 _rot)
	{
		if (m_currentColliderCount == MAX_COLLIDER_SIZE)
		{
			Logging::Logger::Get()->Log(Logging::PRIORITY::WARNING, "You reach the maximum capacity of colliders!");
			return nullptr;
		}

		for (int i = 0; i < m_currentBoxColliderCount; ++i)
		{
			if (m_boxColliders[i].IsDestroyed())
			{
				m_boxColliders[i].Remove();
				m_boxColliders[i].~BoxCollider();
				new (&m_boxColliders[i]) BoxCollider(_isDynamic, _size, _pos, _rot);
				m_boxColliders[i].SetActive(true);
				return &m_boxColliders[i];
			}
		}

		m_boxColliders[m_currentBoxColliderCount].~BoxCollider();
		new (&m_boxColliders[m_currentBoxColliderCount]) BoxCollider(_isDynamic, _size, _pos, _rot);
		m_boxColliders[m_currentBoxColliderCount].SetActive(true);

		++m_currentColliderCount;
		++m_currentBoxColliderCount;

		return &m_boxColliders[m_currentBoxColliderCount - 1];
	}

	void PhysicsSystem::Update(float _deltaTime)
	{
		Logging::Logger::Get()->Log(Logging::PRIORITY::INFO, "PhysicsSystem Update");

		// If you take larger steps than 1 / 60th of a second you need to do multiple collision steps in order to keep the simulation stable. Do 1 collision step per 1 / 60th of a second (round up).
		const int cCollisionSteps = 1;

		// Step the world
		m_physicsSystem.Update(_deltaTime, cCollisionSteps, m_tempAllocator, m_jobSystem);

		// Draw for JoltViewer
		JPH::BodyManager::DrawSettings drawSettings;
		m_physicsSystem.DrawBodies(drawSettings, m_renderer);
		m_renderer->EndFrame();
	}
}