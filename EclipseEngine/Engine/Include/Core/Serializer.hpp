#pragma once
#include "ISerializable.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	using json = nlohmann::ordered_json;

	class Scene;
	class GameObject;
	class Component;
	class Transform;
	class Model;
	class DirectionalLight;
	class PointLight;
	class SpotLight;
	class BoxCollider;
	class CapsuleCollider;
	class MeshCollider;

	class Serializer
	{
	public:
		ECLIPSE_ENGINE void SerializeSceneToFile(Scene* _scene, std::string _filePath);

		ECLIPSE_ENGINE json SerializeScene(Scene* _scene);
		ECLIPSE_ENGINE json SerializeGameObject(GameObject* _gameObject);

	private:
		json SerializeComponent(Component* _component);
		json SerializeTransform(Transform* _transform);
		json SerializeModel(Model* _model);
		json SerializeDirectionalLight(DirectionalLight* _dirLight);
		json SerializePointLight(PointLight* _pointLight);
		json SerializeSpotLight(SpotLight* _spotLight);
		json SerializeBoxCollider(BoxCollider* _boxCollider);
		json SerializeCapsuleCollider(CapsuleCollider* _capsuleCollider);
		json SerializeMeshCollider(MeshCollider* _meshCollider);
	};
}