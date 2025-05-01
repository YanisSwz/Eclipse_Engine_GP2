#include "RHIOpenGL/OpenGLVertexArray.hpp"
#include "RHIOpenGL/OpenGLVertexBuffer.hpp"
using namespace RHI::OpenGL;

OpenGLVertexArray::~OpenGLVertexArray()
{
	Delete();
}

void OpenGLVertexArray::Init()
{
	glGenVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);
}

void RHI::OpenGL::OpenGLVertexArray::LinkVertexBuffer(IVertexBuffer& _vertexBuffer, int _layout, int _numComponents, IFLAGS _type, size_t _stride, void* _offset)
{
	glBindVertexArray(m_ID);
	_vertexBuffer.Bind();
	glEnableVertexAttribArray(_layout);
	glVertexAttribPointer(_layout, _numComponents, CastToOpenGLFlags(_type), GL_FALSE, static_cast<GLsizei>(_stride), _offset);
	_vertexBuffer.Unbind();
	glBindVertexArray(0);
}

void OpenGLVertexArray::Bind()
{
	glBindVertexArray(m_ID);
}

void OpenGLVertexArray::Unbind()
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::Delete()
{
	glDeleteVertexArrays(1, &m_ID);
}