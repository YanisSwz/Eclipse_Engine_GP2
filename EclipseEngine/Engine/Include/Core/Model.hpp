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
		ECLIPSE_ENGINE inline Resource::Mesh* GetMesh() { return m_mesh; }
		ECLIPSE_ENGINE inline Resource::Texture* GetTexture() { return m_texture; }
		ECLIPSE_ENGINE inline Resource::ShaderProgram* GetShader() { return m_shader; }
		ECLIPSE_ENGINE inline std::string GetMeshName() const { if (m_mesh) return m_mesh->name; else return ""; }
		ECLIPSE_ENGINE inline std::string GetTextureName() const { if (m_mesh) return m_texture->name; else return ""; }
		ECLIPSE_ENGINE inline std::string GetShaderName() const { if (m_mesh) return m_shader->name; else return ""; }
		ECLIPSE_ENGINE void SetData(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader);
		ECLIPSE_ENGINE inline void SetMesh(Resource::Mesh* _mesh) { m_mesh = _mesh; }
		ECLIPSE_ENGINE inline void SetTexture(Resource::Texture* _texture) { m_texture = _texture; }
		ECLIPSE_ENGINE inline void SetShader(Resource::ShaderProgram* _shader) { m_shader = _shader; }

	private:
		Resource::Mesh* m_mesh = nullptr;
		Resource::Texture* m_texture = nullptr;
		Resource::ShaderProgram* m_shader = nullptr;
	};

	void to_json(json& _j, const Model& _model);
	void from_json(const json& _j, Model& _model);
}