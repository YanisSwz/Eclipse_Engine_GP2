#include "RHIOpenGL/OpenGLFragmentShader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace RHI::OpenGL;

OpenGLFragmentShader::~OpenGLFragmentShader()
{
    Delete();
}

void OpenGLFragmentShader::Generate(std::string _data)
{    

    // Generate Fragment Shader
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Set Fragment Shader content
    const char* fragmentContent = _data.c_str();
    glShaderSource(m_fragmentShaderID, 1, &fragmentContent, NULL);
    glCompileShader(m_fragmentShaderID);

    // Verify if Fragment Shader compile
    int sucess;
    char infoLog[512];
    glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(m_fragmentShaderID, 512, NULL, infoLog);
        std::cout << "Error : Fragment compilation failed\n" << infoLog << std::endl;
        return;
    }
}

unsigned int RHI::OpenGL::OpenGLFragmentShader::GetID() const
{
    return m_fragmentShaderID;
}

void OpenGLFragmentShader::Delete()
{
    glDeleteShader(m_fragmentShaderID);
}