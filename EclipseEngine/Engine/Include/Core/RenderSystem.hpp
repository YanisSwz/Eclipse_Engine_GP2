#pragma once
#include "Model.hpp"
#include "Lighting/DirectionalLight.hpp"
#include "Lighting/PointLight.hpp"
#include "Lighting/SpotLight.hpp"
#include "ProjectExports.hpp"
#include <vector>

namespace Core
{
	class RenderSystem
	{
	public:
		ECLIPSE_ENGINE RenderSystem() = default;
		ECLIPSE_ENGINE ~RenderSystem() = default;
		ECLIPSE_ENGINE Model* AddModel(Resource::Mesh* _mesh = nullptr, Resource::Texture* _texture = nullptr, Resource::ShaderProgram* _shader = nullptr, bool _bIsDynamic = false);
		ECLIPSE_ENGINE std::vector<Resource::ModelData> GetStaticModels() const;
		ECLIPSE_ENGINE DirectionalLight* AddDirLight();
		ECLIPSE_ENGINE PointLight* AddPointLight();
		ECLIPSE_ENGINE SpotLight* AddSpotLight();

	private:
		static const int MAX_SIZE = 100;
		int m_currentStaticCount = 0;
		int m_currentDynamicCount = 0;
		Model m_staticModels[MAX_SIZE];
		Model m_dynamicModels[MAX_SIZE];

		static const int MAX_LIGHTS_SIZE = 12;
		int m_currentDirCount = 0;
		int m_currentPointCount = 0;
		int m_currentSpotCount = 0;
		DirectionalLight m_directionalLights[MAX_LIGHTS_SIZE];
		PointLight m_pointLights[MAX_LIGHTS_SIZE];
		SpotLight m_spotLights[MAX_LIGHTS_SIZE];
	};
}