#include "RenderSystem.hpp"

namespace Core
{
	Model* RenderSystem::AddModel(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader, bool _bIsDynamic)
	{
		if (_bIsDynamic)
		{
			if (m_currentDynamicCount >= MAX_SIZE)
				return nullptr;

			for (int i = 0; i < m_currentDynamicCount; ++i)
			{
				if (m_dynamicModels[i].IsDestroyed())
				{
					m_dynamicModels[i].Remove();
					m_dynamicModels[i].~Model();
					new (&m_dynamicModels[i]) Model(_mesh, _texture, _shader);
					m_dynamicModels[i].SetActive(true);
					return &m_dynamicModels[i];
				}
			}

			m_dynamicModels[m_currentDynamicCount].~Model();
			new (&m_dynamicModels[m_currentDynamicCount]) Model(_mesh, _texture, _shader);
			m_dynamicModels[m_currentDynamicCount].SetActive(true);
			++m_currentDynamicCount;
			return &m_dynamicModels[m_currentDynamicCount - 1];
		}
		else
		{
			if (m_currentStaticCount >= MAX_SIZE)
				return nullptr;

			for (int i = 0; i < m_currentStaticCount; ++i)
			{
				if (m_staticModels[i].IsDestroyed())
				{
					m_staticModels[i].Remove();
					m_staticModels[i].~Model();
					new (&m_staticModels[i]) Model(_mesh, _texture, _shader);
					m_staticModels[i].SetActive(true);
					return &m_staticModels[i];
				}
			}

			m_staticModels[m_currentStaticCount].~Model();
			new (&m_staticModels[m_currentStaticCount]) Model(_mesh, _texture, _shader);
			m_staticModels[m_currentStaticCount].SetActive(true);
			++m_currentStaticCount;
			return &m_staticModels[m_currentStaticCount - 1];
		}
	}

	DirectionalLight* RenderSystem::AddDirLight()
	{
		if (m_currentDirCount >= MAX_LIGHTS_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentDirCount; ++i)
		{
			if (m_directionalLights[i].IsDestroyed())
			{
				m_directionalLights[i].Remove();
				m_directionalLights[i].~DirectionalLight();
				new (&m_directionalLights[i]) DirectionalLight();
				m_directionalLights[i].SetActive(true);
				return &m_directionalLights[i];
			}
		}

		m_directionalLights[m_currentDirCount].~DirectionalLight();
		new (&m_directionalLights[m_currentDirCount]) DirectionalLight();
		m_directionalLights[m_currentDirCount].SetActive(true);
		++m_currentDirCount;
		return &m_directionalLights[m_currentDirCount - 1];
	}

	PointLight* RenderSystem::AddPointLight()
	{
		if (m_currentPointCount >= MAX_LIGHTS_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentPointCount; ++i)
		{
			if (m_pointLights[i].IsDestroyed())
			{
				m_pointLights[i].Remove();
				m_pointLights[i].~PointLight();
				new (&m_pointLights[i]) PointLight();
				m_pointLights[i].SetActive(true);
				return &m_pointLights[i];
			}
		}

		m_pointLights[m_currentPointCount].~PointLight();
		new (&m_pointLights[m_currentPointCount]) PointLight();
		m_pointLights[m_currentPointCount].SetActive(true);
		++m_currentPointCount;
		return &m_pointLights[m_currentPointCount - 1];
	}

	SpotLight* RenderSystem::AddSpotLight()
	{
		if (m_currentSpotCount >= MAX_LIGHTS_SIZE)
			return nullptr;

		for (int i = 0; i < m_currentSpotCount; ++i)
		{
			if (m_spotLights[i].IsDestroyed())
			{
				m_spotLights[i].Remove();
				m_spotLights[i].~SpotLight();
				new (&m_spotLights[i]) SpotLight();
				m_spotLights[i].SetActive(true);
				return &m_spotLights[i];
			}
		}

		m_spotLights[m_currentSpotCount].~SpotLight();
		new (&m_spotLights[m_currentSpotCount]) SpotLight();
		m_spotLights[m_currentSpotCount].SetActive(true);
		++m_currentSpotCount;
		return &m_spotLights[m_currentSpotCount - 1];
	}

	void RenderSystem::SetAmbientLight(Math::Vec4 _ambientLight)
	{
		m_ambientLight = _ambientLight;
	}

	void RenderSystem::Render(RHI::IRenderInterface* _renderInterface, RHI::IGraphicPipeline* _pipeline, Math::Mat4 _VP, Math::Vec3 _viewPos, std::vector<std::vector<ParticleRenderData>> _particlesData)
	{
		if (_renderInterface != nullptr && _pipeline != nullptr)
		{
			_renderInterface->ClearBackgroundColor(Math::Vec4(0.f, 0.f, 0.f));
			_renderInterface->ClearBuffer(RHI::IFLAGS::COLOR_BUFFER_BIT);
			_renderInterface->ClearBuffer(RHI::IFLAGS::DEPTH_BUFFER_BIT);

			_pipeline->Draw(_VP, _viewPos, GetStaticModels(), m_ambientLight / 255.f, GetDirLights(), GetPointLights(), GetSpotLights(), _particlesData);
		}
	}

	void RenderSystem::Reset()
	{
		m_currentStaticCount = 0;
		m_currentDynamicCount = 0;
		m_currentDirCount = 0;
		m_currentPointCount = 0;
		m_currentSpotCount = 0;
		m_ambientLight = Math::Vec4(1.f, 1.f, 1.f, 0.25f);
	}

	std::vector<Resource::ModelData> RenderSystem::GetStaticModels() const
	{
		std::vector<Resource::ModelData> data;
		for (int i = 0; i < m_currentStaticCount; ++i)
		{
			if (m_staticModels[i].IsActive())
				data.push_back(m_staticModels[i].GetModelData());
		}

		return data;
	}

	std::vector<RHI::DirLightData> RenderSystem::GetDirLights() const
	{
		std::vector<RHI::DirLightData> data;
		for (int i = 0; i < m_currentDirCount; ++i)
		{
			if (m_directionalLights[i].IsActive())
				data.push_back(m_directionalLights[i].GetData());
		}

		return data;
	}

	std::vector<RHI::PointLightData> RenderSystem::GetPointLights() const
	{
		std::vector<RHI::PointLightData> data;
		for (int i = 0; i < m_currentPointCount; ++i)
		{
			if (m_pointLights[i].IsActive())
				data.push_back(m_pointLights[i].GetData());
		}

		return data;
	}

	std::vector<RHI::SpotLightData> RenderSystem::GetSpotLights() const
	{
		std::vector<RHI::SpotLightData> data;
		for (int i = 0; i < m_currentSpotCount; ++i)
		{
			if (m_spotLights[i].IsActive())
				data.push_back(m_spotLights[i].GetData());
		}

		return data;
	}
}