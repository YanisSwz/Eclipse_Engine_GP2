#pragma once
#include "ISerializable.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	using json = nlohmann::ordered_json;

	class Scene;

	class Serializer
	{
	public:
		ECLIPSE_ENGINE void SerializeSceneToFile(Scene* _scene, std::string _filePath);
		ECLIPSE_ENGINE void DeserializeSceneFromFile(Scene* _scene, std::string _filePath);

		ECLIPSE_ENGINE json SerializeScene(Scene* _scene);
		ECLIPSE_ENGINE void DeserializeScene(Scene* _scene, const json& _j);
	};
}