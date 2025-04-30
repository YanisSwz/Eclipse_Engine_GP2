#pragma once
#include "Component.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/Texture.hpp"
#include "Resource/ShaderProgram.hpp"
#include "ModelData.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class GameObject;

	class Model : public Component
	{
	public:
		static meta::factory<Model> factory;

		ECLIPSE_ENGINE Model() = default;
		ECLIPSE_ENGINE Model(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader);
		ECLIPSE_ENGINE ~Model() = default;

		ECLIPSE_ENGINE Resource::ModelData GetModelData() const;
		ECLIPSE_ENGINE void SetData(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader);
		ECLIPSE_ENGINE inline void SetMesh(Resource::Mesh* _mesh) { mesh = _mesh; };
		ECLIPSE_ENGINE inline void SetTexture(Resource::Texture* _texture) { texture = _texture; };
		ECLIPSE_ENGINE inline void SetShader(Resource::ShaderProgram* _shader) { shader = _shader; };

		Resource::Mesh* mesh = nullptr;
		Resource::Texture* texture = nullptr;
		Resource::ShaderProgram* shader = nullptr;
	};
}