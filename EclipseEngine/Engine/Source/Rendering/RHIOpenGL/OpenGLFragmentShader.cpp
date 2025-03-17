#include "RHIOpenGL/OpenGLFragmentShader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace RHI::OpenGL;

OpenGLFragmentShader::~OpenGLFragmentShader()
{
    Delete();
}

void OpenGLFragmentShader::Init(std::string _path)
{    
    // Verify if Fragment file path exists
    std::filesystem::path filePath{ _path };
    if (!std::filesystem::exists(filePath))
        std::cout << "The file: " << filePath << " not found!" << std::endl;

    // Get Fragment file content
    std::ifstream fragFile(filePath);
    std::string fragFileContent((std::istreambuf_iterator<char>(fragFile)), std::istreambuf_iterator<char>());
    
    // Generate Fragment Shader
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Set Fragment Shader content
    const char* fragmentContent = fragFileContent.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentContent, NULL);
    glCompileShader(fragmentShaderID);

    // Verify if Fragment Shader compile
    int sucess;
    char infoLog[512];
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        std::cout << "Error : Fragment compilation failed\n" << infoLog << std::endl;
        return;
    }
}

int RHI::OpenGL::OpenGLFragmentShader::GetID() const
{
    return fragmentShaderID;
}

void OpenGLFragmentShader::Delete()
{
    glDeleteShader(fragmentShaderID);
}