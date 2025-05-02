#include "Model.hpp"
#include "GameObject.hpp"
#include "Resource/ResourceManager.hpp"

namespace Core
{
	meta::factory<Model> Model::factory = meta::reflect<Model>(hash("Model"))
		.data<&Model::SetActive, &Model::IsActive>(hash("IsActive"))
		.data<&Model::m_mesh>(hash("Mesh"))
		.data<&Model::m_texture>(hash("Texture"))
		.data<&Model::m_shader>(hash("Shader"));

	Model::Model(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader)
		:m_mesh(_mesh), m_texture(_texture), m_shader(_shader)
	{

	}

	Resource::ModelData Model::GetModelData() const
	{
		Resource::ModelData modelData;
		modelData.mesh = m_mesh;
		modelData.texture = m_texture;
		modelData.shaderProgram = m_shader;
		modelData.TRS = GetGameObject()->transform->GetTransformMatrix();
		return modelData;
	}

	void Model::SetData(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader) 
	{
		m_mesh = _mesh;
		m_texture = _texture;
		m_shader = _shader;
	}

	void to_json(json& _j, const Model& _model)
	{
		_j = json{
			{"IsActive", _model.IsActive()},
			{"Mesh", _model.GetMeshName()},
			{"Texture", _model.GetTextureName()},
			{"Shader", _model.GetShaderName()}
		};
	}

	void from_json(const json& _j, Model& _model)
	{
		bool bIsActive;
		std::string meshName;
		std::string textureName;
		std::string shaderName;

		_j.at("IsActive").get_to(bIsActive);
		_j.at("Mesh").get_to(meshName);
		_j.at("Texture").get_to(textureName);
		_j.at("Shader").get_to(shaderName);

		Resource::ResourceManager resourceManager = Resource::ResourceManager::GetInstance();

		_model.SetActive(bIsActive);
		_model.SetData(resourceManager.GetResource<Resource::Mesh>(meshName), resourceManager.GetResource<Resource::Texture>(textureName), resourceManager.GetResource<Resource::ShaderProgram>(shaderName));
	}
}