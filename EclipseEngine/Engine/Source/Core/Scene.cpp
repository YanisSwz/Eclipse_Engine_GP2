#include "Scene.hpp"

namespace Core
{
	void Scene::Update()
	{
		transformSystem.Update();
	}

	Transform* Scene::AddTransform(Math::Vec3 _translation, Math::Vec3 _rotation, Math::Vec3 _scale, Transform* _parent)
	{
		return transformSystem.Add(_translation, _rotation, _scale, _parent);
	}

	GameObject* Scene::CreateGameObject()
	{
		if (m_currentGameObjectCount >= MAX_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentGameObjectCount; ++i)
		{
			if (m_gameObjects[i].IsDestroyed())
			{
				new (&m_gameObjects[i]) GameObject(this);
				m_currentGameObject = &m_gameObjects[i];
				return m_currentGameObject;
			}
		}

		new (&m_gameObjects[m_currentGameObjectCount]) GameObject(this);
		m_currentGameObject = &m_gameObjects[m_currentGameObjectCount];
		++m_currentGameObjectCount;
		return m_currentGameObject;
	}

	void Scene::DestroyGameObject()
	{
		if (m_currentGameObject != nullptr)
		{
			m_currentGameObject->Destroy();
			m_currentGameObject = nullptr;
		}
	}

}