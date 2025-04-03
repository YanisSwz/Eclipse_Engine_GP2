#include "RenderSystem.hpp"

//Mesh* AddModel(Mesh* _mesh, Texture* _texture, ShaderProgram* _shader, bool _bIsDynamic)
//{
//	if (m_currentCount >= MAX_SIZE)
//		return nullptr;
// 
//	if (_bIsDynamyic)
//	{
//		m_staticModels[m_currentCount] = Model(_mesh, _texture, _shader);
//		++m_currentCount;
//		return &m_staticModels[m_currentCount];
//	}
//	else
//	{
//		m_dynamicModels[m_currentCount] = Model(_mesh, _texture, _shader);
//		++m_currentCount;
//		return &m_dynamicModels[m_currentCount];
//	}
//}