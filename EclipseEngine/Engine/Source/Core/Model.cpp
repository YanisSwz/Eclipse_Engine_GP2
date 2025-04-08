#include "Model.hpp"

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
}