#pragma once
#include "RHIInterfaces/IVertexBuffer.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLVertexBuffer : public IVertexBuffer
		{
		public:
			OpenGLVertexBuffer() = default;
			~OpenGLVertexBuffer() override;

			void Init(Vertex* _vertices, size_t _size) override;
			void Bind() override;
			void Unbind() override;
			void Delete() override;

		private:
			GLuint ID = GL_NONE;
		};
	}
}