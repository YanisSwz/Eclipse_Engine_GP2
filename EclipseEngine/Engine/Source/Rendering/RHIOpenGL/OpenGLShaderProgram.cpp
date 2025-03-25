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

void OpenGLShaderProgram::SetVertShader(unsigned int _vertShaderID)
{
	glAttachShader(shaderProgramID, _vertShaderID);
}

void OpenGLShaderProgram::SetFragShader(unsigned int _fragShaderID)
{
	glAttachShader(shaderProgramID, _fragShaderID);
}

void OpenGLShaderProgram::Link()
{
	glLinkProgram(shaderProgramID);
}

void OpenGLShaderProgram::LinkVertFragShader(unsigned int _vertShaderID, unsigned int _fragShaderID)
{
	glAttachShader(shaderProgramID, _vertShaderID);
	glAttachShader(shaderProgramID, _fragShaderID);
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

void OpenGLShaderProgram::SetInt(const char* _uniformName, int _value)
{
	glUniform1i(glGetUniformLocation(shaderProgramID, _uniformName), _value);
}

void OpenGLShaderProgram::SetFloat(const char* _uniformName, float _value)
{
	glUniform1f(glGetUniformLocation(shaderProgramID, _uniformName), _value);
}

void OpenGLShaderProgram::SetVec3(const char* _uniformName, Math::Vec3 _vec3)
{
	glUniform3f(glGetUniformLocation(shaderProgramID, _uniformName), _vec3.x, _vec3.y, _vec3.z);
}

void OpenGLShaderProgram::SetVec4(const char* _uniformName, Math::Vec4 _vec4)
{
	glUniform4f(glGetUniformLocation(shaderProgramID, _uniformName), _vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void OpenGLShaderProgram::SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose)
{
	if (_transpose)
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, _uniformName), 1, GL_TRUE, &_mat4.GetValues());
	else
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, _uniformName), 1, GL_FALSE, &_mat4.GetValues());
}

void OpenGLShaderProgram::SetTexture2D(const char* _uniformName, int _textureID)
{
	glUniform1i(glGetUniformLocation(shaderProgramID, _uniformName), _textureID);
}