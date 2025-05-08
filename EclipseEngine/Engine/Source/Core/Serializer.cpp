#include "Serializer.hpp"
#include "Scene.hpp"
#include <fstream>

namespace Core
{
	void Serializer::SerializeSceneToFile(Scene* _scene, std::string _filePath)
	{
		std::ofstream fileStream(_filePath);
		fileStream << std::setw(4) << SerializeScene(_scene) << std::endl;
	}

	void Serializer::DeserializeSceneFromFile(Scene* _scene, std::string _filePath)
	{
		std::ifstream fileStream(_filePath);

		if (!fileStream.is_open() || fileStream.peek() == std::ifstream::traits_type::eof())
		{
			Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "Scene %s is empty or can't be loaded", _filePath.c_str());
			return;
		}

		json scene;
		fileStream >> scene;
		
		DeserializeScene(_scene, scene);
	}

	json Serializer::SerializeScene(Scene* _scene)
	{
		json scene;
		Math::Vec4 ambientLight = _scene->GetSystemManager()->GetRenderSystem()->GetAmbientLight();
		scene["AmbientLight"] = { ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3] };

		std::vector<json> jsonGameObjects;
		GameObject* gameObject;
		for (int i = 0; i < _scene->GetCount(); ++i)
		{
			gameObject = _scene->GetGameObjectByIndex(i);
			if (gameObject->IsDestroyed())
				continue;

			json jsonGameObject;
			gameObject->Serialize(jsonGameObject);
			jsonGameObject[gameObject->name]["Transform"]["ParentIndex"] = _scene->GetGameObjectParentIndex(i);
			jsonGameObjects.push_back(jsonGameObject);
		}
		scene["GameObjects"] = jsonGameObjects;

		return scene;
	}

	void Serializer::DeserializeScene(Scene* _scene, const json& _j)
	{
		float ambientLight[4];
		_j.at("AmbientLight").get_to(ambientLight);
		_scene->GetSystemManager()->GetRenderSystem()->SetAmbientLight({ ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3] });

		json gameObjects = _j.at("GameObjects");
		int gameObjectCount = static_cast<int>(gameObjects.size());

		// Recreate all serialized GameObjects
		for (int i = 0; i < gameObjectCount; ++i)
		{
			json gameObjectJson = gameObjects[i];
			GameObject* gameObject = _scene->CreateGameObject();
			gameObject->Deserialize(gameObjectJson);
		}

		// Recreate Scene graph via Transforms
		for (int i = 0; i < gameObjectCount; ++i)
		{
			GameObject* gameObject = _scene->GetGameObjectByIndex(i);
			int parentIndex = gameObjects[i][gameObject->name]["Transform"]["ParentIndex"];
			if (parentIndex > 0)
			{
				GameObject* parent = _scene->GetGameObjectByIndex(parentIndex);
				if (parent)
					gameObject->transform->SetParent(parent->transform);
			}
		}
	}
}