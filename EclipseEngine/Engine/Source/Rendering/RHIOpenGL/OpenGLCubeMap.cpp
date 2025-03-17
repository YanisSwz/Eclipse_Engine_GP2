#include "RHIOpenGL/OpenGLCubeMap.hpp"
#include "stb_image.h"
#include <iostream>
using namespace RHI::OpenGL;

OpenGLCubeMap::~OpenGLCubeMap()
{
	Delete();
}

void OpenGLCubeMap::Init(std::vector<std::string> _paths)
{
	if (_paths.size() != 6)
		return;

	unsigned char* data;
	int textWidth;
	int textHeight;
	int nrChannels;
	stbi_set_flip_vertically_on_load(false);

	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textID);

	for (int i = 0; i < 6; ++i)
	{
		data = stbi_load(_paths[i].c_str(), &textWidth, &textHeight, &nrChannels, 0);
		if (!data)
		{
			std::cout << "Error during the load of the CubeMap Texture !" << std::endl;
			stbi_image_free(data);
			return;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textWidth, textHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void OpenGLCubeMap::Bind()
{
	glDepthFunc(GL_LEQUAL);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textID);
}

void OpenGLCubeMap::Unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDepthFunc(GL_LESS);
}

void OpenGLCubeMap::Delete()
{
	glDeleteTextures(1, &textID);
}