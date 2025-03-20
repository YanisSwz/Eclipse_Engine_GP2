#pragma once
#include "RHIInterfaces/IFragmentShader.hpp"
#include "ProjectExports.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLFragmentShader : public IFragmentShader
		{
		public:
			ECLIPSE_ENGINE OpenGLFragmentShader() = default;
			ECLIPSE_ENGINE ~OpenGLFragmentShader() override;

			ECLIPSE_ENGINE void Init(std::string _path) override;
			ECLIPSE_ENGINE unsigned int GetID() const override;
			ECLIPSE_ENGINE void Delete() override;

		private:
			GLuint fragmentShaderID = GL_NONE;
		};
	}
}