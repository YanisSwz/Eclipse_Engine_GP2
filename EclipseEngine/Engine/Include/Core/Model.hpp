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
		ECLIPSE_ENGINE Model();
		ECLIPSE_ENGINE Model(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader);
		ECLIPSE_ENGINE ~Model();

		ECLIPSE_ENGINE Resource::ModelData GetModelData() const;

	private:
		Resource::Mesh* m_mesh = nullptr;
		Resource::Texture* m_texture = nullptr;
		Resource::ShaderProgram* m_shader = nullptr;
	};
}