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
	class Camera;
	class AudioSource;
	class AudioListener;

	class Serializer
	{
	public:
		ECLIPSE_ENGINE void SerializeSceneToFile(Scene* _scene, std::string _filePath);
		ECLIPSE_ENGINE void DeserializeSceneFromFile(Scene* _scene, std::string _filePath);

		ECLIPSE_ENGINE json SerializeScene(Scene* _scene);
		ECLIPSE_ENGINE void DeserializeScene(Scene* _scene, const json& _j);


	private:
		json SerializeComponent(Component* _component);
		json SerializeTransform(Transform* _transform, int _parentIndex);
		json SerializeModel(Model* _model);
		json SerializeDirectionalLight(DirectionalLight* _dirLight);
		json SerializePointLight(PointLight* _pointLight);
		json SerializeSpotLight(SpotLight* _spotLight);
		json SerializeBoxCollider(BoxCollider* _boxCollider);
		json SerializeCapsuleCollider(CapsuleCollider* _capsuleCollider);
		json SerializeMeshCollider(MeshCollider* _meshCollider);
		json SerializeCamera(Camera* _camera);
		json SerializeAudioSource(AudioSource* _audioSource);
		json SerializeAudioListener(AudioListener* _audioListener);

		int DeserializeGameObject(GameObject* _gameObject, const json& _j);
	};
}