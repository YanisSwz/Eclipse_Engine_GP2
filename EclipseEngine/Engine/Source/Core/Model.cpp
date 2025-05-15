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
		modelData.ID = GetGameObject()->GetID();
		return modelData;
	}

	void Model::SetData(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader) 
	{
		m_mesh = _mesh;
		m_texture = _texture;
		m_shader = _shader;
	}

	void Model::Serialize(json& _j)
	{
		_j["Model"] = json{
			{"IsActive", IsActive()},
			{"Mesh", GetMeshName()},
			{"Texture", GetTextureName()},
			{"Shader", GetShaderName()}
		};
	}

	void Model::Deserialize(const json& _j)
	{
		bool bIsActive;
		std::string meshName;
		std::string textureName;
		std::string shaderName;

		_j.at("IsActive").get_to(bIsActive);
		_j.at("Mesh").get_to(meshName);
		_j.at("Texture").get_to(textureName);
		_j.at("Shader").get_to(shaderName);

		Resource::ResourceManager* resourceManager = &Resource::ResourceManager::GetInstance();

		SetActive(bIsActive);
		SetData(resourceManager->GetResource<Resource::Mesh>(meshName), resourceManager->GetResource<Resource::Texture>(textureName), resourceManager->GetResource<Resource::ShaderProgram>(shaderName));
	}
}