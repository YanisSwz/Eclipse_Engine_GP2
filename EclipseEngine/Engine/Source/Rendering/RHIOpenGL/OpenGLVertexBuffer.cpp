#include "RHIOpenGL/OpenGLVertexBuffer.hpp"
using namespace RHI::OpenGL; 

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	Delete();
}

void OpenGLVertexBuffer::Init(Vertex* _vertices, size_t _size)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, _size, _vertices, GL_STATIC_DRAW);
}

void OpenGLVertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void OpenGLVertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::Delete()
{
	glDeleteBuffers(1, &m_ID);
}