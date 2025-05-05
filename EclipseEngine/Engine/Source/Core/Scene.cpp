#include "Scene.hpp"

namespace Core
{
	void Scene::Update(float _deltaTime)
	{
		m_systemManager.Update(_deltaTime, m_state);
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

	GameObject* Scene::GetObjectByID(int _id)
	{
		for (int i = 0; i < m_currentGameObjectCount; ++i)
		{
			if (m_gameObjects[i].GetID() == _id)
				return &m_gameObjects[i];
		}
		return nullptr;
	}

	void Scene::SetState(GAME_STATE _state)
	{
		if (_state == GAME_STATE::PAUSE)
			m_systemManager.GetAudioSystem()->SetPause(true);
		else if (_state == GAME_STATE::PLAY && m_state == GAME_STATE::PAUSE)
			m_systemManager.GetAudioSystem()->SetPause(false);
		else if (_state == GAME_STATE::STOP)
			m_systemManager.GetAudioSystem()->Stop();

		m_state = _state;
	}
	
	int Scene::GetGameObjectIndex(GameObject* _gameObject)
	{
		if (!_gameObject)
			return -1;
		
		int id = _gameObject->GetID();
		for (int i = 0; i < m_currentGameObjectCount; ++i)
		{
			if (m_gameObjects[i].GetID() == id)
				return i;
		}

		return -1;
	}

	int Scene::GetGameObjectParentIndex(int _index)
	{
		if (_index < 0 || _index > MAX_SIZE)
			return -1;

		GameObject* parent = nullptr;
		Transform* parentTransform = m_gameObjects[_index].transform->GetParent();
		if (parentTransform)
		{
			parent = parentTransform->GetGameObject();
			return GetGameObjectIndex(parent);
		}

		return -1;
	}

	void Scene::Reset()
	{
		for (int i = 0; i < m_currentGameObjectCount; ++i)
			m_gameObjects[i].Destroy();
	}
}