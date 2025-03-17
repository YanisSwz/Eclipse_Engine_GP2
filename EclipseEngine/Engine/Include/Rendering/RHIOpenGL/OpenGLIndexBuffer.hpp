#pragma once
#include "RHIInterfaces/IIndexBuffer.hpp"
#include <Glad/glad.h>

namespace RHI
{
	class IVertexArray;

	namespace OpenGL
	{
		class OpenGLIndexBuffer : public IIndexBuffer
		{
		public:
			OpenGLIndexBuffer() = default;
			~OpenGLIndexBuffer() override;

			void Init(unsigned int* _indices, size_t _size) override;
			void Draw(IVertexArray* _vertexArray) override;
			void Bind() override;
			void Unbind() override;
			void Delete() override;

		private:
			GLuint ID = GL_NONE;
		};
	}
}