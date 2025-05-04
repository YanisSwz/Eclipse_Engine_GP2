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

void OpenGLShaderProgram::SetVertShader(unsigned int _vertShaderID)
{
	glAttachShader(m_shaderProgramID, _vertShaderID);
}

void OpenGLShaderProgram::SetFragShader(unsigned int _fragShaderID)
{
	glAttachShader(m_shaderProgramID, _fragShaderID);
}

void OpenGLShaderProgram::Link()
{
	glLinkProgram(m_shaderProgramID);
}

void OpenGLShaderProgram::LinkVertFragShader(unsigned int _vertShaderID, unsigned int _fragShaderID)
{
	glAttachShader(m_shaderProgramID, _vertShaderID);
	glAttachShader(m_shaderProgramID, _fragShaderID);
	glLinkProgram(m_shaderProgramID);
	GLint success;
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		success;
		GLchar infoLog[512];
		glGetProgramInfoLog(m_shaderProgramID, 512, NULL, infoLog);
		std::cout << "error" << std::endl;
	}
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

void OpenGLShaderProgram::SetInt(const char* _uniformName, int _value)
{
	glUniform1i(glGetUniformLocation(m_shaderProgramID, _uniformName), _value);
}

void OpenGLShaderProgram::SetFloat(const char* _uniformName, float _value)
{
	glUniform1f(glGetUniformLocation(m_shaderProgramID, _uniformName), _value);
}

void OpenGLShaderProgram::SetVec3(const char* _uniformName, Math::Vec3 _vec3)
{
	glUniform3f(glGetUniformLocation(m_shaderProgramID, _uniformName), _vec3.x, _vec3.y, _vec3.z);
}

void OpenGLShaderProgram::SetVec4(const char* _uniformName, Math::Vec4 _vec4)
{
	glUniform4f(glGetUniformLocation(m_shaderProgramID, _uniformName), _vec4.x, _vec4.y, _vec4.z, _vec4.w);
}

void OpenGLShaderProgram::SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose)
{
	if (_transpose)
		glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, _uniformName), 1, GL_TRUE, &_mat4.GetValues());
	else
		glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, _uniformName), 1, GL_FALSE, &_mat4.GetValues());
}

void OpenGLShaderProgram::SetTexture2D(const char* _uniformName, int _textureID)
{
	glUniform1i(glGetUniformLocation(m_shaderProgramID, _uniformName), _textureID);
}