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
	shaderProgramID = glCreateProgram();
}

void OpenGLShaderProgram::SetVertShader(const IVertexShader& _vertexShader)
{
	glAttachShader(shaderProgramID, _vertexShader.GetID());
}

void OpenGLShaderProgram::SetFragShader(const IFragmentShader& _fragmentShader)
{
	glAttachShader(shaderProgramID, _fragmentShader.GetID());
}

void OpenGLShaderProgram::Link()
{
	glLinkProgram(shaderProgramID);
}

void OpenGLShaderProgram::LinkVertFragShader(const IVertexShader& _vertexShader, const IFragmentShader& _fragmentShader)
{
	glAttachShader(shaderProgramID, _vertexShader.GetID());
	glAttachShader(shaderProgramID, _fragmentShader.GetID());
	glLinkProgram(shaderProgramID);
}

int OpenGLShaderProgram::GetProgram() const
{
	return shaderProgramID;
}

void OpenGLShaderProgram::Bind()
{
	glUseProgram(shaderProgramID);
}

void OpenGLShaderProgram::Unbind()
{
	glUseProgram(0);
}

void OpenGLShaderProgram::Delete()
{
	glDeleteProgram(shaderProgramID);
}

void OpenGLShaderProgram::SetTexture2D(const char* _uniformName, int _textureID)
{
	glUniform1i(glGetUniformLocation(shaderProgramID, _uniformName), _textureID);
}

void RHI::OpenGL::OpenGLShaderProgram::SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose)
{
	if (_transpose)
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, _uniformName), 1, GL_TRUE, &_mat4.GetValues());
	else
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, _uniformName), 1, GL_FALSE, &_mat4.GetValues());
}
