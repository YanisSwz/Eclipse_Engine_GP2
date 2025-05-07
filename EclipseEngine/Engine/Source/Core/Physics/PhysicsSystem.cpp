#include "Physics/PhysicsSystem.hpp"
#include "Core/GameObject.hpp"
#include "Logging/Logger.hpp"

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>

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

	Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, buffer);
}

namespace Core
{
	PhysicsSystem::PhysicsSystem()
	{
		if (JPH::Factory::sInstance == nullptr)
		{
			JPH::RegisterDefaultAllocator();
			JPH::Trace = TraceImpl;
			JPH::Factory::sInstance = new JPH::Factory();

			JPH::RegisterTypes();
			m_tempAllocator = new JPH::TempAllocatorImpl{ 10 * 1024 * 1024 }; // Pre-allocating 10 MB for the physics update

			m_jobSystem = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);

			const JPH::uint cMaxBodies = MAX_COLLIDER_SIZE;
			// This determines how many mutexes to allocate to protect rigid bodies from concurrent access. Set it to 0 for the default settings.
			const JPH::uint cNumBodyMutexes = 0;
			const JPH::uint cMaxBodyPairs = MAX_COLLIDER_SIZE;
			const JPH::uint cMaxContactConstraints = MAX_COLLIDER_SIZE;

			m_contactListener.Init(this);
			m_physicsSystem.SetContactListener(&m_contactListener);

			// Now we can create the actual physics system.
			m_physicsSystem.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, m_broadPhaseLayerInterface, m_objectVsBroadphaseLayerFilter, m_objectVsObjectLayerFilter);

			m_bodyInterface = &m_physicsSystem.GetBodyInterface();

#ifdef _DEBUG
			m_rendererFile.open("testScene.jor", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
			m_rendererStream = new JPH::StreamOutWrapper(m_rendererFile);
			m_renderer = new JPH::DebugRendererRecorder(*m_rendererStream);
#endif // _DEBUG
		}
	}

	PhysicsSystem::~PhysicsSystem()
	{
		for (int i = 0; i < m_currentBoxColliderCount; ++i)
			m_boxColliders[i].Delete();
		for (int i = 0; i < m_currentCapsuleColliderCount; ++i)
			m_capsuleColliders[i].Delete();
		for (int i = 0; i < m_currentMeshColliderCount; ++i)
			m_meshColliders[i].Delete();

		JPH::UnregisterTypes();
		delete JPH::Factory::sInstance;
		JPH::Factory::sInstance = nullptr;

		delete m_jobSystem;
		delete m_tempAllocator;

#ifdef _DEBUG
		delete m_renderer;
		delete m_rendererStream;
		m_rendererFile.close();
#endif // _DEBUG
	}

	BoxCollider* PhysicsSystem::AddBoxCollider()
	{
		if (m_currentColliderCount >= MAX_COLLIDER_SIZE)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Maximum capacity of colliders reached!");
			return nullptr;
		}

		for (int i = 0; i < m_currentBoxColliderCount; ++i)
		{
			if (m_boxColliders[i].IsDestroyed())
			{
				m_boxColliders[i].Remove();
				m_boxColliders[i].~BoxCollider();
				new (&m_boxColliders[i]) BoxCollider(m_bodyInterface);
				m_boxColliders[i].SetActive(true);
				return &m_boxColliders[i];
			}
		}

		m_boxColliders[m_currentBoxColliderCount].~BoxCollider();
		new (&m_boxColliders[m_currentBoxColliderCount]) BoxCollider(m_bodyInterface);
		m_boxColliders[m_currentBoxColliderCount].SetActive(true);

		++m_currentColliderCount;
		++m_currentBoxColliderCount;

		return &m_boxColliders[m_currentBoxColliderCount - 1];
	}

	CapsuleCollider* PhysicsSystem::AddCapsuleCollider()
	{
		if (m_currentColliderCount >= MAX_COLLIDER_SIZE)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Maximum capacity of colliders reached!");
			return nullptr;
		}

		for (int i = 0; i < m_currentCapsuleColliderCount; ++i)
		{
			if (m_capsuleColliders[i].IsDestroyed())
			{
				m_capsuleColliders[i].Remove();
				m_capsuleColliders[i].~CapsuleCollider();
				new (&m_capsuleColliders[i]) CapsuleCollider(m_bodyInterface);
				m_capsuleColliders[i].SetActive(true);
				return &m_capsuleColliders[i];
			}
		}

		m_capsuleColliders[m_currentCapsuleColliderCount].~CapsuleCollider();
		new (&m_capsuleColliders[m_currentCapsuleColliderCount]) CapsuleCollider(m_bodyInterface);
		m_capsuleColliders[m_currentCapsuleColliderCount].SetActive(true);

		++m_currentColliderCount;
		++m_currentCapsuleColliderCount;

		return &m_capsuleColliders[m_currentCapsuleColliderCount - 1];
	}

	MeshCollider* PhysicsSystem::AddMeshCollider()
	{
		if (m_currentColliderCount >= MAX_COLLIDER_SIZE)
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Maximum capacity of colliders reached!");
			return nullptr;
		}

		for (int i = 0; i < m_currentMeshColliderCount; ++i)
		{
			if (m_meshColliders[i].IsDestroyed())
			{
				m_meshColliders[i].Remove();
				m_meshColliders[i].~MeshCollider();
				new (&m_meshColliders[i]) MeshCollider(m_bodyInterface);
				m_meshColliders[i].SetActive(true);
				return &m_meshColliders[i];
			}
		}

		m_meshColliders[m_currentMeshColliderCount].~MeshCollider();
		new (&m_meshColliders[m_currentMeshColliderCount]) MeshCollider(m_bodyInterface);
		m_meshColliders[m_currentMeshColliderCount].SetActive(true);

		++m_currentColliderCount;
		++m_currentMeshColliderCount;

		return &m_meshColliders[m_currentMeshColliderCount - 1];
	}

	void PhysicsSystem::CallOnCollisionEnter(const JPH::Body& _body1, const JPH::Body& _body2)
	{
		ICollider* collider1 = FindCollider(_body1.GetID());
		if (!collider1)
			return;
		ICollider* collider2 = FindCollider(_body2.GetID());
		if (!collider2)
			return;

		Core::GameObject* gameObject1 = collider1->GetGameObject();
		if (gameObject1)
		{
			Core::MonoBehaviour* colliderScript1 = gameObject1->GetComponent<Core::MonoBehaviour>();
			if (colliderScript1)
				colliderScript1->OnCollisionEnter(collider2);
		}

		Core::GameObject* gameObject2 = collider2->GetGameObject();
		if (gameObject2)
		{
			Core::MonoBehaviour* colliderScript2 = gameObject2->GetComponent<Core::MonoBehaviour>();
			if (colliderScript2)
				colliderScript2->OnCollisionEnter(collider1);
		}
	}

	void PhysicsSystem::CallOnCollisionStay(const JPH::Body& _body1, const JPH::Body& _body2)
	{
		ICollider* collider1 = FindCollider(_body1.GetID());
		if (!collider1)
			return;
		ICollider* collider2 = FindCollider(_body2.GetID());
		if (!collider2)
			return;

		Core::GameObject* gameObject1 = collider1->GetGameObject();
		if (gameObject1)
		{
			Core::MonoBehaviour* colliderScript1 = gameObject1->GetComponent<Core::MonoBehaviour>();
			if (colliderScript1)
				colliderScript1->OnCollisionStay(collider2);
		}

		Core::GameObject* gameObject2 = collider2->GetGameObject();
		if (gameObject2)
		{
			Core::MonoBehaviour* colliderScript2 = gameObject2->GetComponent<Core::MonoBehaviour>();
			if (colliderScript2)
				colliderScript2->OnCollisionStay(collider1);
		}
	}

	void PhysicsSystem::CallOnCollisionExit(const JPH::BodyID& _body1, const JPH::BodyID& _body2)
	{
		ICollider* collider1 = FindCollider(_body1);
		if (!collider1)
			return;
		ICollider* collider2 = FindCollider(_body2);
		if (!collider2)
			return;

		Core::GameObject* gameObject1 = collider1->GetGameObject();
		if (gameObject1)
		{
			Core::MonoBehaviour* colliderScript1 = gameObject1->GetComponent<Core::MonoBehaviour>();
			if (colliderScript1)
				colliderScript1->OnCollisionExit(collider2);
		}

		Core::GameObject* gameObject2 = collider2->GetGameObject();
		if (gameObject2)
		{
			Core::MonoBehaviour* colliderScript2 = gameObject2->GetComponent<Core::MonoBehaviour>();
			if (colliderScript2)
				colliderScript2->OnCollisionExit(collider1);
		}
	}

	ICollider* PhysicsSystem::FindCollider(const JPH::BodyID& _bodyID)
	{
		for (int i = 0; i < m_currentBoxColliderCount; ++i)
		{
			if (m_boxColliders[i].GetBodyID() == _bodyID)
				return &m_boxColliders[i];
		}

		for (int i = 0; i < m_currentCapsuleColliderCount; ++i)
		{
			if (m_capsuleColliders[i].GetBodyID() == _bodyID)
				return &m_capsuleColliders[i];
		}

		for (int i = 0; i < m_currentMeshColliderCount; ++i)
		{
			if (m_meshColliders[i].GetBodyID() == _bodyID)
				return &m_meshColliders[i];
		}

		return nullptr;
	}

	void PhysicsSystem::Update(float _deltaTime)
	{
		if (bFirstUpdate)
		{
			bFirstUpdate = false;
			_deltaTime = 0.f;

			GameObject* GO;
			Math::Quat rotationQuat{ 0.f, 0.f, 0.f, 0.f };
			for (int i = 0; i < m_currentBoxColliderCount; ++i)
			{
				GO = m_boxColliders[i].GetGameObject();
				if (GO)
				{
					if (!GO->IsActive())
						continue;
					m_boxColliders[i].SetPosition(GO->transform->GetPosition() + GO->transform->GetRotation().Rotate(m_boxColliders[i].GetOffsetPos()));
					m_boxColliders[i].SetRotation(Math::Quat::Normalized(GO->transform->GetRotation()));
				}
			}
			for (int i = 0; i < m_currentCapsuleColliderCount; ++i)
			{
				GO = m_capsuleColliders[i].GetGameObject();
				if (GO)
				{
					if (!GO->IsActive())
						continue;
					m_capsuleColliders[i].SetPosition(GO->transform->GetPosition() + GO->transform->GetRotation().Rotate(m_capsuleColliders[i].GetOffsetPos()));
					m_capsuleColliders[i].SetRotation(Math::Quat::Normalized(GO->transform->GetRotation()));
				}
			}
			for (int i = 0; i < m_currentMeshColliderCount; ++i)
			{
				GO = m_meshColliders[i].GetGameObject();
				if (GO)
				{
					if (!GO->IsActive())
						continue;
					m_meshColliders[i].SetPosition(GO->transform->GetPosition() + GO->transform->GetRotation().Rotate(m_meshColliders[i].GetOffsetPos()));
					m_meshColliders[i].SetRotation(Math::Quat::Normalized(GO->transform->GetRotation()));
				}
			}
		}

		GameObject* GO;
		Math::Quat rotationQuat{ 0.f, 0.f, 0.f, 0.f };
		for (int i = 0; i < m_currentBoxColliderCount; ++i)
		{
			GO = m_boxColliders[i].GetGameObject();
			if (GO)
			{
				if (!GO->IsActive())
					continue;
				if (GO->transform->HasPositionChanged() || GO->transform->HasRotationChanged())
				{
					m_boxColliders[i].SetPosition(GO->transform->GetPosition() + GO->transform->GetRotation().Rotate(m_boxColliders[i].GetOffsetPos()));
					m_boxColliders[i].SetRotation(Math::Quat::Normalized(GO->transform->GetRotation()));
				}
			}
		}
		for (int i = 0; i < m_currentCapsuleColliderCount; ++i)
		{
			GO = m_capsuleColliders[i].GetGameObject();
			if (GO)
			{
				if (!GO->IsActive())
					continue;
				if (GO->transform->HasPositionChanged() || GO->transform->HasRotationChanged())
				{
					m_capsuleColliders[i].SetPosition(GO->transform->GetPosition() + GO->transform->GetRotation().Rotate(m_capsuleColliders[i].GetOffsetPos()));
					m_capsuleColliders[i].SetRotation(Math::Quat::Normalized(GO->transform->GetRotation()));
				}
			}
		}
		for (int i = 0; i < m_currentMeshColliderCount; ++i)
		{
			GO = m_meshColliders[i].GetGameObject();
			if (GO)
			{
				if (!GO->IsActive())
					continue;
				if (GO->transform->HasPositionChanged() || GO->transform->HasRotationChanged())
				{
					m_meshColliders[i].SetPosition(GO->transform->GetPosition() + GO->transform->GetRotation().Rotate(m_meshColliders[i].GetOffsetPos()));
					m_meshColliders[i].SetRotation(Math::Quat::Normalized(GO->transform->GetRotation()));
				}
			}
		}


		m_physicsSystem.Update(_deltaTime, 1, m_tempAllocator, m_jobSystem);

#ifdef _DEBUG
		// Draw for JoltViewer
		JPH::BodyManager::DrawSettings drawSettings;
		m_physicsSystem.DrawBodies(drawSettings, m_renderer);
		m_renderer->EndFrame();
#endif // _DEBUG


		for (int i = 0; i < m_currentBoxColliderCount; ++i)
		{
			GO = m_boxColliders[i].GetGameObject();
			if (GO)
			{
				if (!GO->IsActive())
					continue;
				GO->transform->SetPosition(m_boxColliders[i].GetPosition() - m_boxColliders[i].GetOffsetPosRotated());
				rotationQuat = m_boxColliders[i].GetRotation();
				GO->transform->SetRotation(rotationQuat);
			}
		}
		for (int i = 0; i < m_currentCapsuleColliderCount; ++i)
		{
			GO = m_capsuleColliders[i].GetGameObject();
			if (GO)
			{
				if (!GO->IsActive())
					continue;
				GO->transform->SetPosition(m_capsuleColliders[i].GetPosition() - m_capsuleColliders[i].GetOffsetPosRotated());
				rotationQuat = m_capsuleColliders[i].GetRotation();
				GO->transform->SetRotation(rotationQuat);
			}
		}
		for (int i = 0; i < m_currentMeshColliderCount; ++i)
		{
			GO = m_meshColliders[i].GetGameObject();
			if (GO)
			{
				if (!GO->IsActive())
					continue;
				GO->transform->SetPosition(m_meshColliders[i].GetPosition() - m_meshColliders[i].GetOffsetPosRotated());
				rotationQuat = m_meshColliders[i].GetRotation();
				GO->transform->SetRotation(rotationQuat);
			}
		}
	}

	void PhysicsSystem::Reset()
	{
		m_currentColliderCount = 0;
		m_currentBoxColliderCount = 0;
		m_currentCapsuleColliderCount = 0;
		m_currentMeshColliderCount = 0;
		bFirstUpdate = true;
	}
}