#pragma once
#include "RHIInterfaces/IFragmentShader.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLFragmentShader : public IFragmentShader
		{
		public:
			OpenGLFragmentShader() = default;
			~OpenGLFragmentShader() override;

			void Init(std::string _path) override;
			unsigned int GetID() const override;
			void Delete() override;

		private:
			GLuint fragmentShaderID = GL_NONE;
		};
	}
}