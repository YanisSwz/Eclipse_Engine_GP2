#pragma once
#include <vector>
#include "GameObject.hpp"
#include "TransformSystem.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class Scene
	{
	public:
		ECLIPSE_ENGINE Scene() = default;
		ECLIPSE_ENGINE ~Scene() = default;
		ECLIPSE_ENGINE Transform* AddTransform(Math::Vec3 _translation = { 0.f, 0.f, 0.f }, Math::Vec3 _rotation = { 0.f, 0.f, 0.f }, Math::Vec3 _scale = { 1.f, 1.f, 1.f });

	private:
		TransformSystem transformSystem{};
		GameObject* m_root = nullptr;
		GameObject* m_currentGameObject = nullptr;
	};
}