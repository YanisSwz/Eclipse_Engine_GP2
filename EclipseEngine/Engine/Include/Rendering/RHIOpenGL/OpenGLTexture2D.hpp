#pragma once
#include "RHIInterfaces/ITexture2D.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLTexture2D : public ITexture2D
		{
		public:
			OpenGLTexture2D() = default;
			~OpenGLTexture2D() override;

			void Init(std::string _path) override;
			void Bind() override;
			void Unbind() override;
			unsigned int GetID() const override;
			void Delete() override;

		private:
			GLuint textureID = GL_NONE;
		};
	}
}