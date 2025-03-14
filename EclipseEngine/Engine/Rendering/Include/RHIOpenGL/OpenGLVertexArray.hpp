#pragma once
#include "RHIInterfaces/IVertexArray.hpp"
#include "RHIInterfaces/IFlags.hpp"
#include <Glad/glad.h>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLVertexArray : public IVertexArray
		{
		public:
			OpenGLVertexArray() = default;
			~OpenGLVertexArray() override;

			void Init() override;
			void LinkVertexBuffer(IVertexBuffer& _vertexBuffer, int _layout, int _numComponents, IFLAGS _type, size_t _stride, void* _offset) override;
			void Bind() override;
			void Unbind() override;
			void Delete() override;

		private:
			GLuint ID = GL_NONE;
		};
	}
}