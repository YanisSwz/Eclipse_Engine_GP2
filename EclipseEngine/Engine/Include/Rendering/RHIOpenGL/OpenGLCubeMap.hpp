#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "RHIInterfaces/ICubeMap.hpp"
#include "ProjectExports.hpp"
#include <Glad/glad.h>


namespace RHI
{
	namespace OpenGL
	{
		class OpenGLCubeMap : public ICubeMap
		{
		public:
			ECLIPSE_ENGINE OpenGLCubeMap() = default;
			ECLIPSE_ENGINE ~OpenGLCubeMap() override;

			ECLIPSE_ENGINE void Init(std::vector<std::string> _paths) override;
			ECLIPSE_ENGINE void Bind() override;
			ECLIPSE_ENGINE void Unbind() override;
			ECLIPSE_ENGINE void Delete() override;

		private:
			GLuint textID = GL_NONE;
		};
	}
}