#include "Serializer.hpp"
#include "Scene.hpp"
#include "Transform.hpp"
#include "Model.hpp"
#include "Lighting/DirectionalLight.hpp"
#include "Lighting/PointLight.hpp"
#include "Lighting/SpotLight.hpp"
#include "Physics/BoxCollider.hpp"
#include "Physics/CapsuleCollider.hpp"
#include "Physics/MeshCollider.hpp"
#include "Camera/Camera.hpp"
#include "Audio/AudioSource.hpp"
#include "Audio/AudioListener.hpp"
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
		json scene;
		fileStream >> scene;
		
		DeserializeScene(_scene, scene);
	}

	json Serializer::SerializeScene(Scene* _scene)
	{
		json scene;
		Math::Vec4 ambientLight = _scene->GetSystemManager()->GetRenderSystem()->GetAmbientLight();
		scene["AmbientLight"] = { ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3] };

		std::vector<json> gameObjects;
		for (int i = 0; i < _scene->GetCount(); ++i)
		{
			json gameObject;
			_scene->GetGameObject(i)->Serialize(gameObject);
			gameObject[_scene->GetGameObject(i)->name]["Transform"]["ParentIndex"] = _scene->GetGameObjectParentIndex(i);
			gameObjects.push_back(gameObject);
		}
		scene["GameObjects"] = gameObjects;

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
			GameObject* gameObject = _scene->GetGameObject(i);
			int parentIndex = gameObjects[i][gameObject->name]["Transform"]["ParentIndex"];
			if (parentIndex > 0)
			{
				GameObject* parent = _scene->GetGameObject(parentIndex);
				if (parent)
					gameObject->transform->SetParent(parent->transform);
			}
		}
	}
}