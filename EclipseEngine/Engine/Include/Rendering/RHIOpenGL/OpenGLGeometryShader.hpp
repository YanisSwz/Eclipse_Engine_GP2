#pragma once
#include "RHIInterfaces/IGeometryShader.hpp"
#include "ProjectExports.hpp"
#include <glad/glad.h>

namespace RHI::OpenGL
{
	class OpenGLGeometryShader : public IGeometryShader
	{
	public:
		ECLIPSE_ENGINE OpenGLGeometryShader() = default;
		ECLIPSE_ENGINE ~OpenGLGeometryShader() override;

		ECLIPSE_ENGINE void Generate(std::string _path) override;
		ECLIPSE_ENGINE unsigned int GetID() const override;
		ECLIPSE_ENGINE void Delete() override;

	private:
		GLuint m_geometryShaderID = GL_NONE;
	};
}