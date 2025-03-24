#include "RHIOpenGL/OpenGLVertexShader.hpp"
#include "RHIOpenGL/OpenGLFragmentShader.hpp"
#include "RHIOpenGL/OpenGLShaderProgram.hpp"
#include "RHIInterfaces/Vertex.hpp"
#include <iostream>
using namespace RHI::OpenGL;

OpenGLShaderProgram::~OpenGLShaderProgram()
{
	Delete();
}

void OpenGLShaderProgram::CreateProgram()
{
	m_shaderProgramID = glCreateProgram();
}

void OpenGLShaderProgram::SetVertShader(const IVertexShader& _vertexShader)
{
	glAttachShader(m_shaderProgramID, _vertexShader.GetID());
}

void OpenGLShaderProgram::SetFragShader(const IFragmentShader& _fragmentShader)
{
	glAttachShader(m_shaderProgramID, _fragmentShader.GetID());
}

void OpenGLShaderProgram::Link()
{
	glLinkProgram(m_shaderProgramID);
}

void OpenGLShaderProgram::LinkVertFragShader(const IVertexShader& _vertexShader, const IFragmentShader& _fragmentShader)
{
	glAttachShader(m_shaderProgramID, _vertexShader.GetID());
	glAttachShader(m_shaderProgramID, _fragmentShader.GetID());
	glLinkProgram(m_shaderProgramID);
}

int OpenGLShaderProgram::GetProgram() const
{
	return m_shaderProgramID;
}

void OpenGLShaderProgram::Bind()
{
	glUseProgram(m_shaderProgramID);
}

void OpenGLShaderProgram::Unbind()
{
	glUseProgram(0);
}

void OpenGLShaderProgram::Delete()
{
	glDeleteProgram(m_shaderProgramID);
}

void OpenGLShaderProgram::SetTexture2D(const char* _uniformName, int _textureID)
{
	glUniform1i(glGetUniformLocation(m_shaderProgramID, _uniformName), _textureID);
}

void RHI::OpenGL::OpenGLShaderProgram::SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose)
{
	if (_transpose)
		glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, _uniformName), 1, GL_TRUE, &_mat4.GetValues());
	else
		glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, _uniformName), 1, GL_FALSE, &_mat4.GetValues());
}
