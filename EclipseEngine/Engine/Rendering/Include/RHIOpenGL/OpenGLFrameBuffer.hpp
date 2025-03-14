#pragma once
#include "RHIInterfaces/IFrameBuffer.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLFrameBuffer : public IFrameBuffer
		{
		public:
			OpenGLFrameBuffer() = default;
			~OpenGLFrameBuffer() override;

			void Init(int _width, int _height) override;
			void Rescale(int _width, int _height) override;
			void Bind() override;
			void Unbind() override;
			unsigned int GetTextureID() const override;
			void Delete() override;

		private:
			int width = 0;
			int height = 0;

			GLuint textID = GL_NONE;
			GLuint fboID = GL_NONE;
			GLuint rboID = GL_NONE;
		};
	}
}