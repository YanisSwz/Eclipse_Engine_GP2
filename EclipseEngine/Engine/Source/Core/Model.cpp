#include "Model.hpp"
#include "GameObject.hpp"

namespace Core
{
	Model::Model()
	{
	}

	Model::Model(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader)
		:mesh(_mesh), texture(_texture), shader(_shader)
	{

	}

	Model::~Model()
	{
	}

	Resource::ModelData Model::GetModelData() const
	{
		Resource::ModelData modelData;
		modelData.mesh = mesh;
		modelData.texture = texture;
		modelData.shaderProgram = shader;
		modelData.TRS = GetGameObject()->transform->GetTransformMatrix();
		return modelData;
	}

	void Model::SetData(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader) 
	{
		mesh = _mesh;
		texture = _texture;
		shader = _shader;
	}
}