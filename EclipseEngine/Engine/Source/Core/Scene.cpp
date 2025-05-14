#include "Scene.hpp"
#include <cmath>

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
		m_gameObjects[m_currentGameObjectCount].tag = GameObject::GetTags()[0];
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
		AudioSystem* audioSystem = m_systemManager.GetAudioSystem();
		if (_state == GAME_STATE::PAUSE)
			audioSystem->SetPause(true);
		else if (_state == GAME_STATE::PLAY && m_state == GAME_STATE::STOP)
		{
			audioSystem->Stop();
			audioSystem->Start();
		}
		else if (_state == GAME_STATE::PLAY && m_state == GAME_STATE::PAUSE)
			audioSystem->SetPause(false);
		else if (_state == GAME_STATE::STOP)
		{
			audioSystem->Stop();
			if (!audioSystem->IsAudioEnabled())
				audioSystem->EnableAudio();
		}

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
		m_currentGameObjectCount = 0;
		m_systemManager.Reset();
	}

	void Scene::SerializeToFile(std::string _filePath)
	{
		std::ofstream fileStream(_filePath);
		fileStream << std::setw(4) << Serialize() << std::endl;
	}

	void Scene::DeserializeFromFile(std::string _filePath)
	{
		std::ifstream fileStream(_filePath);

		if (!fileStream.is_open() || fileStream.peek() == std::ifstream::traits_type::eof())
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "Scene %s is empty or can't be loaded", _filePath.c_str());
			return;
		}

		json scene;
		fileStream >> scene;

		Deserialize(scene);
	}

	json Scene::Serialize()
	{
		json scene;
		Math::Vec4 ambientLight = GetSystemManager()->GetRenderSystem()->GetAmbientLight();
		scene["AmbientLight"] = { ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3] };

		std::vector<json> jsonGameObjects;
		GameObject* gameObject;
		int destroyedNb = 0;
		for (int i = 0; i < GetCount(); ++i)
		{
			gameObject = GetGameObjectByIndex(i);

			if (gameObject->IsDestroyed())
			{
				++destroyedNb;
				continue;
			}

			json jsonGameObject;
			gameObject->Serialize(jsonGameObject);
			int index = GetGameObjectParentIndex(i);
			if (index >= 0)
				index = std::max(index - destroyedNb, -1);
			jsonGameObject[gameObject->name]["Transform"]["ParentIndex"] =  index;
			jsonGameObjects.push_back(jsonGameObject);
		}
		scene["GameObjects"] = jsonGameObjects;

		return scene;
	}

	void Scene::Deserialize(const json& _j)
	{
		float ambientLight[4];
		_j.at("AmbientLight").get_to(ambientLight);
		GetSystemManager()->GetRenderSystem()->SetAmbientLight({ ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3] });

		json gameObjects = _j.at("GameObjects");
		int gameObjectCount = static_cast<int>(gameObjects.size());

		// Recreate all serialized GameObjects
		for (int i = 0; i < gameObjectCount; ++i)
		{
			json gameObjectJson = gameObjects[i];
			GameObject* gameObject = CreateGameObject();
			gameObject->Deserialize(gameObjectJson);
		}

		// Recreate Scene graph via Transforms
		for (int i = 0; i < gameObjectCount; ++i)
		{
			GameObject* gameObject = GetGameObjectByIndex(i);
			int parentIndex = gameObjects[i][gameObject->name]["Transform"]["ParentIndex"];
			if (parentIndex > 0)
			{
				GameObject* parent = GetGameObjectByIndex(parentIndex);
				if (parent)
					gameObject->transform->SetParent(parent->transform);
			}
		}
	}

	void Scene::SavePrefab(GameObject* _gameObject, Resource::Prefab* _prefab)
	{
		std::string filePath = "Assets/Prefabs/" + _prefab->name + ".json";
	}

	GameObject* Scene::InstantiatePrefab(GameObject* _parent, Resource::Prefab* _prefab)
	{
		std::string filePath = "Assets/Prefabs/" + _prefab->name + ".json";

		std::ifstream fileStream(filePath);

		if (!fileStream.is_open() || fileStream.peek() == std::ifstream::traits_type::eof())
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::ERROR, "Prefab at %s is empty or can't be loaded", filePath.c_str());
			return nullptr;
		}

		json prefab;
		fileStream >> prefab;

		int gameObjectCount = static_cast<int>(prefab.size());
		std::vector<GameObject*> gameObjects;

		// Recreate all serialized GameObjects
		for (int i = 0; i < gameObjectCount; ++i)
		{
			json gameObjectJson = prefab[i];
			gameObjects.push_back(CreateGameObject());
			gameObjects[i]->Deserialize(gameObjectJson);
		}

		// Recreate Scene graph via Transforms
		for (int i = 0; i < gameObjects.size(); ++i)
		{
			GameObject* gameObject = gameObjects[i];
			int parentIndex = prefab[i][gameObject->name]["Transform"]["ParentIndex"];
			if (parentIndex > 0 && parentIndex < gameObjects.size())
			{
				GameObject* parent = gameObjects[parentIndex];
				if (parent)
					gameObject->transform->SetParent(parent->transform);
			}
		}

		return gameObjects.empty() ? nullptr : gameObjects[0];
	}
}