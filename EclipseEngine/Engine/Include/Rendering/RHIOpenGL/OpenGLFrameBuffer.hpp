#pragma once
#include "RHIInterfaces/IFrameBuffer.hpp"
#include "ProjectExports.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLFrameBuffer : public IFrameBuffer
		{
		public:
			ECLIPSE_ENGINE OpenGLFrameBuffer() = default;
			ECLIPSE_ENGINE ~OpenGLFrameBuffer() override;

			ECLIPSE_ENGINE void Init(int _width, int _height) override;
			ECLIPSE_ENGINE void Rescale(int _width, int _height) override;
			ECLIPSE_ENGINE void Bind() override;
			ECLIPSE_ENGINE void Unbind() override;
			ECLIPSE_ENGINE unsigned int GetTextureID() const override;
			ECLIPSE_ENGINE unsigned int GetFrameBufferID() const override;
			ECLIPSE_ENGINE unsigned int GetDepthBufferID() const override;
			ECLIPSE_ENGINE void Delete() override;

		private:

			GLuint m_textID = GL_NONE;
			GLuint m_fboID = GL_NONE;
			GLuint m_rboID = GL_NONE;
		};
	}
}