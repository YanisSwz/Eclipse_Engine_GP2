#pragma once
#include "Model.hpp"
#include "ProjectExports.hpp"

namespace Core
{
	class RenderSystem
	{
	public:
		ECLIPSE_ENGINE RenderSystem() = default;
		ECLIPSE_ENGINE ~RenderSystem() = default;
		ECLIPSE_ENGINE Model* AddModel(Resource::Mesh* _mesh, Resource::Texture* _texture, Resource::ShaderProgram* _shader, bool _bIsDynamic);

	private:
		static const int MAX_SIZE = 100;
		int m_currentStaticCount = 0;
		int m_currentDynamicCount = 0;
		Model m_staticModels[MAX_SIZE];
		Model m_dynamicModels[MAX_SIZE];
	};
}