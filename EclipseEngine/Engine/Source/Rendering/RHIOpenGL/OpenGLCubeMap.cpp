#include "RHIOpenGL/OpenGLCubeMap.hpp"
#include "stb_image.h"
#include <iostream>

namespace RHI::OpenGL
{
	OpenGLCubeMap::~OpenGLCubeMap()
	{
		Delete();
	}

	void OpenGLCubeMap::Generate(std::vector<unsigned char*> _data, int _width, int _height, Resource::TEXTURE_EXTENSION _textureExtention)
	{
		if (_data.size() != 6)
			return;

		glGenTextures(1, &m_textID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textID);

		for (int i = 0; i < 6; ++i)
		{
			switch (_textureExtention)
			{
			case Resource::TEXTURE_EXTENSION::PNG:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data[i]);
				break;
			case Resource::TEXTURE_EXTENSION::JPG:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data[i]);
				break;
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void OpenGLCubeMap::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textID);
	}

	void OpenGLCubeMap::Unbind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void OpenGLCubeMap::Delete()
	{
		glDeleteTextures(1, &m_textID);
	}
}