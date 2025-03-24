#include "RHIOpenGL/OpenGLVertexShader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace RHI::OpenGL;

OpenGLVertexShader::~OpenGLVertexShader()
{
    Delete();
}

void OpenGLVertexShader::Init(std::string _path)
{
    // Verify if Vertex file path exists
    std::filesystem::path filePath{ _path };
    if (!std::filesystem::exists(filePath))
    {
        std::cout << "The file: " << filePath << " not found!" << std::endl;
        return;
    }
    
    // Get Vertex file content
    std::ifstream vertFile(filePath);
    std::string vertFileContent((std::istreambuf_iterator<char>(vertFile)), std::istreambuf_iterator<char>());

    // Generate Vertex Shader
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    // Set Vertex Shader content
    const char* vertexContent = vertFileContent.c_str();
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