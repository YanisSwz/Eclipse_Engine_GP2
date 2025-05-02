#include "RHIOpenGL/OpenGLIndexBuffer.hpp"
#include "RHIInterfaces/IVertexArray.hpp"
using namespace RHI::OpenGL;

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	Delete();
}

void OpenGLIndexBuffer::Init(unsigned int* _indices, size_t _size)
{
	for (int i = 0; i < _size / sizeof(unsigned int); ++i)
		indexBuffer.push_back(_indices[i]);

	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size, _indices, GL_STATIC_DRAW);
}

void OpenGLIndexBuffer::Draw(IVertexArray* _vertexArray)
{
	_vertexArray->Bind();
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indexBuffer.size()), GL_UNSIGNED_INT, 0);
	_vertexArray->Unbind();
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