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

void OpenGLTexture2D::Init(std::string _path)
{
	// Verify if Texture file path exists
	if (!std::filesystem::exists(_path))
	{
		std::cout << "The file: " << _path << " not found!" << std::endl;
		return;
	}

	// Get Texture file content
	int widthImg = 0, heightImg = 0, numColCh = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(_path.c_str(), &widthImg, &heightImg, &numColCh, 0);

	// Generate Texture
	glGenTextures(1, &m_textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture2D::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void OpenGLTexture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int OpenGLTexture2D::GetID() const
{
	return m_textureID;
}

void OpenGLTexture2D::Delete()
{
	glDeleteTextures(1, &m_textureID);
}