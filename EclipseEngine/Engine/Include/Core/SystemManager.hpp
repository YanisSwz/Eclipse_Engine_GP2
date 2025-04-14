#pragma once
#include "ProjectExports.hpp"
#include "TransformSystem.hpp"
#include "RenderSystem.hpp"

namespace Core
{
	class SystemManager
	{
	public:
		ECLIPSE_ENGINE SystemManager() = default;
		ECLIPSE_ENGINE ~SystemManager() = default;

		ECLIPSE_ENGINE void Update();
		ECLIPSE_ENGINE Transform* AddTransform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f }, Transform* _parent = nullptr);
		ECLIPSE_ENGINE Transform* GetTransforms() const;

	private:
		TransformSystem m_transformSystem{};
		RenderSystem m_renderSystem{};
	};
}