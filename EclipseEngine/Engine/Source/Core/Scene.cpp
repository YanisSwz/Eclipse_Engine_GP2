#include "Scene.hpp"

namespace Core
{
	Transform* Scene::AddTransform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale)
	{
		return transformSystem.Add(_translation, _rotation, _scale);
	}

	void Scene::CreateGameObject()
	{
		if (m_currentGameObjectCount >= MAX_SIZE)
			return;

		for (int i = 0; i < m_currentGameObjectCount; ++i)
		{
			if (m_gameObjects[i].IsDestroyed())
			{
				m_gameObjects[i] = GameObject(this);
				return;
			}
		}

		m_gameObjects[m_currentGameObjectCount] = GameObject(this);
		++m_currentGameObjectCount;
	}
}