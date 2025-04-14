#pragma once
#include "ProjectExports.hpp"
#include "TransformSystem.hpp"
#include "RenderSystem.hpp"
#include <vector>

namespace Core
{
	class SystemManager
	{
	public:
		ECLIPSE_ENGINE SystemManager() = default;
		ECLIPSE_ENGINE ~SystemManager() = default;

		ECLIPSE_ENGINE void Update();
		ECLIPSE_ENGINE Transform* AddTransform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f }, Transform* _parent = nullptr);
		ECLIPSE_ENGINE Transform* GetTransformsRoot() const;
		ECLIPSE_ENGINE std::vector<Resource::ModelData> GetStaticModels() const;

		template <typename T>
		T* AddComponent()
		{
			T* basePtr = new T();

			if (Model* d_ptr = dynamic_cast<Model*>(basePtr))
			{
				delete basePtr;
				return m_renderSystem.AddModel();
			}

			delete basePtr;
			return nullptr;
		}

	private:
		TransformSystem m_transformSystem{};
		RenderSystem m_renderSystem{};
	};
}