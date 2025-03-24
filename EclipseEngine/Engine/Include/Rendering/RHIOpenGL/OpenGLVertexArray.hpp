#pragma once
#include "RHIInterfaces/IVertexArray.hpp"
#include "RHIInterfaces/IFlags.hpp"
#include "ProjectExports.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLVertexArray : public IVertexArray
		{
		public:
			ECLIPSE_ENGINE OpenGLVertexArray() = default;
			ECLIPSE_ENGINE ~OpenGLVertexArray() override;

			ECLIPSE_ENGINE void Init() override;
			ECLIPSE_ENGINE void LinkVertexBuffer(IVertexBuffer& _vertexBuffer, int _layout, int _numComponents, IFLAGS _type, size_t _stride, void* _offset) override;
			ECLIPSE_ENGINE void Bind() override;
			ECLIPSE_ENGINE void Unbind() override;
			ECLIPSE_ENGINE void Delete() override;

		private:
			GLuint m_ID = GL_NONE;
		};
	}
}