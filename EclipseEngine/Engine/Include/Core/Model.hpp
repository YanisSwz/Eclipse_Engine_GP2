#pragma once
#include "Component.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/Texture.hpp"
#include "Resource/ShaderProgram.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class Model : public Component
	{
	public:
		ECLIPSE_ENGINE Model();
		ECLIPSE_ENGINE Model(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader);
		ECLIPSE_ENGINE ~Model();

	private:
		Resource::Mesh* m_mesh = nullptr;
		Resource::Texture* m_texture = nullptr;
		Resource::ShaderProgram* m_shader = nullptr;
	};
}