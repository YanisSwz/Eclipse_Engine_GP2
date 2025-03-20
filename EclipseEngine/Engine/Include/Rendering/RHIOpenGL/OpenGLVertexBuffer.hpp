#pragma once
#include "RHIInterfaces/IVertexBuffer.hpp"
#include "ProjectExports.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLVertexBuffer : public IVertexBuffer
		{
		public:
			ECLIPSE_ENGINE OpenGLVertexBuffer() = default;
			ECLIPSE_ENGINE ~OpenGLVertexBuffer() override;

			ECLIPSE_ENGINE void Init(Vertex* _vertices, size_t _size) override;
			ECLIPSE_ENGINE void Bind() override;
			ECLIPSE_ENGINE void Unbind() override;
			ECLIPSE_ENGINE void Delete() override;

		private:
			GLuint ID = GL_NONE;
		};
	}
}