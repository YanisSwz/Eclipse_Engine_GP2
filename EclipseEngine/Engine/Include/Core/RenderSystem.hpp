#pragma once
#include "ProjectExports.hpp"

namespace Core
{
	class RenderSystem
	{
	public:
		ECLIPSE_ENGINE RenderSystem() = default;
		ECLIPSE_ENGINE ~RenderSystem() = default;
		// ECLIPSE_ENGINE Model* AddModel(Mesh* _mesh, Texture* _texture, ShaderProgram* _shader, bool _bIsDynamic);

	private:
		static const int MAX_SIZE = 100;
		int m_currentCount = 0;
		// Model m_staticModels[MAX_SIZE];
		// Model m_dynamicModels[MAX_SIZE];
	};
}