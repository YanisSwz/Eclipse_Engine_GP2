#include "RHIOpenGL/OpenGLIndexBuffer.hpp"
#include "RHIInterfaces/IVertexArray.hpp"
using namespace RHI::OpenGL;

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	Delete();
}

void OpenGLIndexBuffer::Init(unsigned int* _indices, size_t _size)
{
	for (int i = 0; i < _size / sizeof(uint32_t); ++i)
		indexBuffer.push_back(_indices[i]);

	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size, _indices, GL_STATIC_DRAW);
}

void OpenGLIndexBuffer::Draw(IVertexArray* _vertexArray)
{
	_vertexArray->Bind();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexBuffer.size()), GL_UNSIGNED_INT, 0);
}

void OpenGLIndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void OpenGLIndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLIndexBuffer::Delete()
{
	glDeleteBuffers(1, &m_ID);
}