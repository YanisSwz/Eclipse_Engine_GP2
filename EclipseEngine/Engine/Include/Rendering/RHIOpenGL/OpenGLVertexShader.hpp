#pragma once
#include "RHIInterfaces/IVertexShader.hpp"
#include <glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLVertexShader : public IVertexShader
		{
		public:
			OpenGLVertexShader() = default;
			~OpenGLVertexShader() override;

			void Init(std::string _path) override;
			int GetID() const override;
			void Delete() override;

		private:
			GLuint vertexShaderID = GL_NONE;
		};
	}
}