#pragma once
#include "RHIInterfaces/IVertexShader.hpp"
#include "ProjectExports.hpp"
#include <glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLVertexShader : public IVertexShader
		{
		public:
			ECLIPSE_ENGINE OpenGLVertexShader() = default;
			ECLIPSE_ENGINE ~OpenGLVertexShader() override;

			ECLIPSE_ENGINE void Generate(std::string _data) override;
			ECLIPSE_ENGINE unsigned int GetID() const override;
			ECLIPSE_ENGINE void Delete() override;

		private:
			GLuint m_vertexShaderID = GL_NONE;
		};
	}
}