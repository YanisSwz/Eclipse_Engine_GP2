#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "RHIInterfaces/ICubeMap.hpp"
#include "ProjectExports.hpp"
#include <Glad/glad.h>


namespace RHI::OpenGL
{
	class OpenGLCubeMap : public ICubeMap
	{
	public:
		ECLIPSE_ENGINE OpenGLCubeMap() = default;
		ECLIPSE_ENGINE ~OpenGLCubeMap() override;

		ECLIPSE_ENGINE void Generate(std::vector<unsigned char*> _data, int _width, int _height, Resource::TEXTURE_EXTENSION _textureExtention) override;
		ECLIPSE_ENGINE void Bind() override;
		ECLIPSE_ENGINE void Unbind() override;
		ECLIPSE_ENGINE void Delete() override;

	private:
		GLuint m_textID = GL_NONE;
	};
}