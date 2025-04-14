#pragma once
#include <vector>
#include "GameObject.hpp"
#include "SystemManager.hpp"
#include "ProjectExports.hpp"
#include <type_traits>

namespace Core
{
	class Scene
	{
	public:
		ECLIPSE_ENGINE Scene() = default;
		ECLIPSE_ENGINE ~Scene() = default;

		ECLIPSE_ENGINE void Update();
		ECLIPSE_ENGINE GameObject* CreateGameObject();
		ECLIPSE_ENGINE SystemManager* GetSystemManager();
		
	private:
		static const int MAX_SIZE = 100;
		int m_currentGameObjectCount = 0;
		GameObject m_gameObjects[MAX_SIZE];

		SystemManager m_systemManager{};
	};
}