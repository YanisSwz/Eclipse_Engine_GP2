#pragma once
#include "RHIInterfaces/ITexture2D.hpp"
#include "ProjectExports.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLTexture2D : public ITexture2D
		{
		public:
			ECLIPSE_ENGINE OpenGLTexture2D() = default;
			ECLIPSE_ENGINE ~OpenGLTexture2D() override;

			ECLIPSE_ENGINE void Init(std::string _path) override;
			ECLIPSE_ENGINE void Bind() override;
			ECLIPSE_ENGINE void Unbind() override;
			ECLIPSE_ENGINE unsigned int GetID() const override;
			ECLIPSE_ENGINE void Delete() override;

		private:
			GLuint m_textureID = GL_NONE;
		};
	}
}