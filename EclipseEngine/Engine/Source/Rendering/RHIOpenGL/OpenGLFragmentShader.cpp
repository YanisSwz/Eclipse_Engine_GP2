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
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Set Fragment Shader content
    const char* fragmentContent = _data.c_str();
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

unsigned int RHI::OpenGL::OpenGLFragmentShader::GetID() const
{
    return fragmentShaderID;
}

void OpenGLFragmentShader::Delete()
{
    glDeleteShader(fragmentShaderID);
}