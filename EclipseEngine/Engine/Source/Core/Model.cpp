#include "Model.hpp"
#include "GameObject.hpp"

namespace Core
{
	meta::factory<Model> Model::factory = meta::reflect<Model>(hash("Model"))
		.data<&Model::SetActive, &Model::IsActive>(m_hash("IsActive"))
		.data<&Model::mesh>(m_hash("Mesh"))
		.data<&Model::texture>(m_hash("Texture"))
		.data<&Model::shader>(m_hash("Shader"));

	Model::Model(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader)
		:mesh(_mesh), texture(_texture), shader(_shader)
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