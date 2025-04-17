#include "Scene.hpp"

namespace Core
{
	void Scene::Update(float _deltaTime)
	{
		m_systemManager.Update(_deltaTime);
	}

	GameObject* Scene::CreateGameObject()
	{
		if (m_currentGameObjectCount >= MAX_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentGameObjectCount; ++i)
		{
			if (m_gameObjects[i].IsDestroyed())
			{
				m_gameObjects[i].~GameObject();
				new (&m_gameObjects[i]) GameObject(&m_systemManager);
				return &m_gameObjects[i];
			}
		}

		m_gameObjects[m_currentGameObjectCount].~GameObject();
		new (&m_gameObjects[m_currentGameObjectCount]) GameObject(&m_systemManager);
		++m_currentGameObjectCount;
		return &m_gameObjects[m_currentGameObjectCount - 1];
	}

	SystemManager* Scene::GetSystemManager() 
	{
		return &m_systemManager;
	}

}