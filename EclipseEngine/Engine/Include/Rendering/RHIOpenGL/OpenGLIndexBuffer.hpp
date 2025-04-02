#pragma once
#include "RHIInterfaces/IIndexBuffer.hpp"
#include "ProjectExports.hpp"
#include <Glad/glad.h>

namespace RHI
{
	class IVertexArray;

	namespace OpenGL
	{
		class OpenGLIndexBuffer : public IIndexBuffer
		{
		public:
			ECLIPSE_ENGINE OpenGLIndexBuffer() = default;
			ECLIPSE_ENGINE ~OpenGLIndexBuffer() override;

			ECLIPSE_ENGINE void Init(unsigned int* _indices, size_t _size) override;
			ECLIPSE_ENGINE void Draw(IVertexArray* _vertexArray) override;
			ECLIPSE_ENGINE void Bind() override;
			ECLIPSE_ENGINE void Unbind() override;
			ECLIPSE_ENGINE void Delete() override;

		private:
			GLuint m_ID = GL_NONE;
		};
	}
}