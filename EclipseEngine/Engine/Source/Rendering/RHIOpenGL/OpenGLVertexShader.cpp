#include "RHIOpenGL/OpenGLVertexShader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace RHI::OpenGL;

OpenGLVertexShader::~OpenGLVertexShader()
{
    Delete();
}

void OpenGLVertexShader::Generate(std::string _data)
{
    // Generate Vertex Shader
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    // Set Vertex Shader content
    const char* vertexContent = _data.c_str();
    glShaderSource(m_vertexShaderID, 1, &vertexContent, NULL);
    glCompileShader(m_vertexShaderID);
    
    // Verify if Vertex Shader compile
    int sucess;
    char infoLog[512];
    glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(m_vertexShaderID, 512, NULL, infoLog);
        std::cout << "Error : Vertex compilation failed\n" << infoLog << std::endl;
        return;
    }
}

unsigned int OpenGLVertexShader::GetID() const
{
    return m_vertexShaderID;
}

void OpenGLVertexShader::Delete()
{
    glDeleteShader(m_vertexShaderID);
}