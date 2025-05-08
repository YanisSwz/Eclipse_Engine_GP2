#pragma once
#include "RHIInterfaces/IRenderInterface.hpp"
#include "RHIInterfaces/IPipeline/IGraphicPipeline.hpp"
#include "Model.hpp"
#include "Lighting/DirectionalLight.hpp"
#include "Lighting/PointLight.hpp"
#include "Lighting/SpotLight.hpp"
#include "RHIInterfaces/Lights.hpp"
#include "ProjectExports.hpp"
#include "Particles/ParticleRenderData.hpp"
#include <vector>

namespace Core
{
	class RenderSystem
	{
	public:
		ECLIPSE_ENGINE RenderSystem() = default;
		ECLIPSE_ENGINE ~RenderSystem() = default;

		ECLIPSE_ENGINE inline Math::Vec4 GetAmbientLight() const { return m_ambientLight; }

		ECLIPSE_ENGINE Model* AddModel(Resource::Mesh* _mesh = nullptr, Resource::Texture* _texture = nullptr, Resource::ShaderProgram* _shader = nullptr, bool _bIsDynamic = false);
		ECLIPSE_ENGINE DirectionalLight* AddDirLight();
		ECLIPSE_ENGINE PointLight* AddPointLight();
		ECLIPSE_ENGINE SpotLight* AddSpotLight();
		ECLIPSE_ENGINE void SetAmbientLight(Math::Vec4 _ambientLight);

		ECLIPSE_ENGINE void Render(RHI::IRenderInterface* _renderInterface, RHI::IGraphicPipeline* _pipeline, Math::Mat4 _VP, Math::Vec3 _viewPos, std::vector<std::vector<ParticleRenderData>> _particlesData);

		ECLIPSE_ENGINE void Reset();

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
		Math::Vec4 m_ambientLight = Math::Vec4(1.f, 1.f, 1.f, 0.25f);

		std::vector<Resource::ModelData> GetStaticModels() const;

		std::vector<RHI::DirLightData> GetDirLights() const;
		std::vector<RHI::PointLightData> GetPointLights() const;
		std::vector<RHI::SpotLightData> GetSpotLights() const;
	};
}