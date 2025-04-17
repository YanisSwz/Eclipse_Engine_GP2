#pragma once
#include "ProjectExports.hpp"
#include "TransformSystem.hpp"
#include "RenderSystem.hpp"
#include "Physics/PhysicsSystem.hpp"
#include <vector>

namespace Core
{
	class SystemManager
	{
	public:
		ECLIPSE_ENGINE SystemManager() = default;
		ECLIPSE_ENGINE ~SystemManager() = default;

		ECLIPSE_ENGINE void Update(float _deltaTime);
		ECLIPSE_ENGINE Transform* AddTransform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f }, Transform* _parent = nullptr);
		ECLIPSE_ENGINE Transform* GetTransformsRoot() const;
		ECLIPSE_ENGINE std::vector<Resource::ModelData> GetStaticModels() const;

		template <typename T>
		T* AddComponent()
		{
			T* basePtr = new T();

			if (Model* dynamicModel_ptr = dynamic_cast<Model*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_renderSystem.AddModel());
			}
			else if (BoxCollider* dynamicBoxCollider_ptr = dynamic_cast<BoxCollider*>(basePtr))
			{
				delete basePtr;
				return dynamic_cast<T*>(m_physicsSystem.AddBoxCollider());
			}

			delete basePtr;
			return nullptr;
		}

	private:
		TransformSystem m_transformSystem{};
		RenderSystem m_renderSystem{};
		PhysicsSystem m_physicsSystem{};
	};
}