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

	std::vector<Resource::ModelData> RenderSystem::GetStaticModels() const
	{
		std::vector<Resource::ModelData> data;
		for (int i = 0; i < m_currentStaticCount; ++i)
		{
			if(m_staticModels[i].IsActive())
				data.push_back(m_staticModels[i].GetModelData());
		}
		
		return data;
	}
}