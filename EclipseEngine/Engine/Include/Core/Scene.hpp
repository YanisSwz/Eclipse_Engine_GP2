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

		TransformSystem transformSystem;

	private:
		GameObject* m_root = nullptr;
		GameObject* m_currentGameObject = nullptr;

	};
}