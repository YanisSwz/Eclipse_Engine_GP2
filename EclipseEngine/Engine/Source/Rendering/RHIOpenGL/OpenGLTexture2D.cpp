#include "RHIOpenGL/OpenGLTexture2D.hpp"
#include <stb_image.h>
#include <filesystem>
#include <iostream>
#include <string>
using namespace RHI::OpenGL;

OpenGLTexture2D::~OpenGLTexture2D()
{
	Delete();
}

void OpenGLTexture2D::Generate(unsigned char* _data, int _width, int _height)
{
	// Generate Texture
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture2D::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void OpenGLTexture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int OpenGLTexture2D::GetID() const
{
	return textureID;
}

void OpenGLTexture2D::Delete()
{
	glDeleteTextures(1, &textureID);
}