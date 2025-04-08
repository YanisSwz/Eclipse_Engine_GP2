#include "RenderSystem.hpp"

namespace Core
{
	Model* RenderSystem::AddModel(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader, bool _bIsDynamic)
	{
		if (m_currentCount >= MAX_SIZE)
			return nullptr;
	 
		if (_bIsDynamic)
		{
			new (&m_staticModels[m_currentCount]) Model(_mesh, _texture, _shader);
			++m_currentCount;
			return &m_staticModels[m_currentCount];
		}
		else
		{
			new (&m_dynamicModels[m_currentCount]) Model(_mesh, _texture, _shader);
			++m_currentCount;
			return &m_dynamicModels[m_currentCount];
		}
	}
}