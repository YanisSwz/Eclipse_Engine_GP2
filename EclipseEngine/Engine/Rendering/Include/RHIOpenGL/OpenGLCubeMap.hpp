#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "RHIInterfaces/ICubeMap.hpp"
#include <Glad/glad.h>


namespace RHI
{
	namespace OpenGL
	{
		class OpenGLCubeMap : public ICubeMap
		{
		public:
			OpenGLCubeMap() = default;
			~OpenGLCubeMap() override;

			void Init(std::vector<std::string> _paths) override;
			void Bind() override;
			void Unbind() override;
			void Delete() override;

		private:
			GLuint textID = GL_NONE;
		};
	}
}