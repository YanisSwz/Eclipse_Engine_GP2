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
#include <fstream>

namespace Core
{
	void Serializer::SerializeSceneToFile(Scene* _scene, std::string _filePath)
	{
		std::ofstream o(_filePath);
		o << std::setw(4) << SerializeScene(_scene) << std::endl;
	}

	void Serializer::DeserializeSceneFromFile(Scene* _scene, std::string _filePath)
	{
		std::ifstream i(_filePath);
		json scene;
		i >> scene;

		float ambientLight[4];
		scene.at("AmbientLight").get_to(ambientLight);
		_scene->GetSystemManager()->GetRenderSystem()->SetAmbientLight({ ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3] });

		json gameObjects = scene.at("GameObjects");
		int gameObjectCount = static_cast<int>(gameObjects.size());

		for (int i = 0; i < gameObjectCount; ++i)
		{
			json gameObjectJson = gameObjects[i];

			GameObject* gameObject = _scene->CreateGameObject();
		}
	}

	json Serializer::SerializeScene(Scene* _scene)
	{
		json scene;
		Math::Vec4 ambientLight = _scene->GetSystemManager()->GetRenderSystem()->GetAmbientLight();
		scene["AmbientLight"] = { ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3] };

		std::vector<json> gameObjects;
		for (int i = 0; i < _scene->GetCount(); ++i)
			gameObjects.push_back(SerializeGameObject(_scene->GetGameObject(i), _scene->GetGameObjectParentIndex(i)));
		
		scene["GameObjects"] = gameObjects;

		return scene;
	}

	json Serializer::SerializeGameObject(GameObject* _gameObject, int _parentIndex)
	{
		json gameObject;
		gameObject[_gameObject->name]["IsActive"] = _gameObject->IsActive();
		gameObject[_gameObject->name]["Transform"] = SerializeTransform(_gameObject->transform, _parentIndex);

		std::vector<Component*> components = _gameObject->GetComponents();
		std::vector<json> componentsJson;
		for (int i = 0; i < components.size(); ++i)
			componentsJson.push_back(SerializeComponent(components[i]));
		gameObject[_gameObject->name]["Components"] = componentsJson;

		return gameObject;
	}

	json Serializer::SerializeComponent(Component* _component)
	{
		json component;

		if (Model* dynamicModel_ptr = dynamic_cast<Model*>(_component))
		{
			component["Model"] = SerializeModel(dynamicModel_ptr);
		}
		else if (DirectionalLight* dynamicDirectionalLight_ptr = dynamic_cast<DirectionalLight*>(_component))
		{
			component["DirectionalLight"] = SerializeDirectionalLight(dynamicDirectionalLight_ptr);
		}
		else if (PointLight* dynamicPointLight_ptr = dynamic_cast<PointLight*>(_component))
		{
			component["PointLight"] = SerializePointLight(dynamicPointLight_ptr);
		}
		else if (SpotLight* dynamicSpotLight_ptr = dynamic_cast<SpotLight*>(_component))
		{
			component["SpotLight"] = SerializeSpotLight(dynamicSpotLight_ptr);
		}
		else if (BoxCollider* dynamicBoxCollider_ptr = dynamic_cast<BoxCollider*>(_component))
		{
			component["BoxCollider"] = SerializeBoxCollider(dynamicBoxCollider_ptr);
		}
		else if (CapsuleCollider* dynamicCapsuleCollider_ptr = dynamic_cast<CapsuleCollider*>(_component))
		{
			component["CapsuleCollider"] = SerializeCapsuleCollider(dynamicCapsuleCollider_ptr);
		}
		else if (MeshCollider* dynamicMeshCollider_ptr = dynamic_cast<MeshCollider*>(_component))
		{
			component["MeshCollider"] = SerializeMeshCollider(dynamicMeshCollider_ptr);
		}

		return component;
	}

	json Serializer::SerializeTransform(Transform* _transform, int _parentIndex)
	{
		json j = *_transform;
		j["ParentIndex"] = _parentIndex;
		return j;
	}

	json Serializer::SerializeModel(Model* _model)
	{
		json j = *_model;
		return j;
	}

	json Serializer::SerializeDirectionalLight(DirectionalLight* _dirLight)
	{
		json j = *_dirLight;
		return j;
	}

	json Serializer::SerializePointLight(PointLight* _pointLight)
	{
		json j = *_pointLight;
		return j;
	}

	json Serializer::SerializeSpotLight(SpotLight* _spotLight)
	{
		json j = *_spotLight;
		return j;
	}

	json Serializer::SerializeBoxCollider(BoxCollider* _boxCollider)
	{
		json j = *_boxCollider;
		return j;
	}

	json Serializer::SerializeCapsuleCollider(CapsuleCollider* _capsuleCollider)
	{
		json j = *_capsuleCollider;
		return j;
	}

	json Serializer::SerializeMeshCollider(MeshCollider* _meshCollider)
	{
		json j = *_meshCollider;
		return j;
	}

	void Serializer::DeserializeGameObject(GameObject* _gameObject, json _j)
	{
		return;
	}
}