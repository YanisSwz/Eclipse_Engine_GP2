#include "Model.hpp"
#include "GameObject.hpp"

namespace Core
{
	Model::Model()
	{
	}

	Model::Model(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader)
		:m_mesh(_mesh), m_texture(_texture), m_shader(_shader)
	{

	}

	Model::~Model()
	{
	}

	Resource::ModelData Model::GetModelData() const
	{
		Resource::ModelData modelData;
		modelData.mesh = m_mesh;
		modelData.texture = m_texture;
		modelData.shaderProgram = m_shader;
		modelData.TRS = GetGameObject()->GetComponent<Core::Transform>()->GetTransformMatrix();
		return modelData;
	}
}