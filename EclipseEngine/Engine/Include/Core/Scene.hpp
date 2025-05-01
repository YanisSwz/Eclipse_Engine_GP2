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

		ECLIPSE_ENGINE void Update(float _deltaTime);
		ECLIPSE_ENGINE GameObject* CreateGameObject();
		ECLIPSE_ENGINE SystemManager* GetSystemManager();
		ECLIPSE_ENGINE inline int GetCount() { return m_currentGameObjectCount; }
		ECLIPSE_ENGINE inline GameObject* GetGameObject(int _index) { return (_index < MAX_SIZE)  ? &m_gameObjects[_index] : nullptr; }

	private:
		static const int MAX_SIZE = 100;
		int m_currentGameObjectCount = 0;
		GameObject m_gameObjects[MAX_SIZE];

		SystemManager m_systemManager{};
	};
}