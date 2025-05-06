#include "RHIOpenGL/OpenGLGeometryShader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace RHI::OpenGL
{
	OpenGLGeometryShader::~OpenGLGeometryShader()
	{
		Delete();
	}

	void OpenGLGeometryShader::Generate(std::string _data)
	{
		// Generate Geometry Shader
		m_geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

		// Set Geometry Shader content
		const char* fragmentContent = _data.c_str();
		glShaderSource(m_geometryShaderID, 1, &fragmentContent, NULL);
		glCompileShader(m_geometryShaderID);

		// Verify if Geometry Shader compile
		int sucess;
		char infoLog[512];
		glGetShaderiv(m_geometryShaderID, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			glGetShaderInfoLog(m_geometryShaderID, 512, NULL, infoLog);
			std::cout << "Error : Geometry compilation failed\n" << infoLog << std::endl;
			return;
		}
	}

	unsigned int OpenGLGeometryShader::GetID() const
	{
		return m_geometryShaderID;
	}

	void OpenGLGeometryShader::Delete()
	{
		glDeleteShader(m_geometryShaderID);
	}
}