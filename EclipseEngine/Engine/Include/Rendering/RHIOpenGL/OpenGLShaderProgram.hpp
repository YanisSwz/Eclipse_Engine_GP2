#pragma once
#include "RHIInterfaces/IShaderProgram.hpp"
#include "Maths.hpp"
#include "ProjectExports.hpp"
#include <string>

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLShaderProgram : public IShaderProgram
		{
		public:
			ECLIPSE_ENGINE OpenGLShaderProgram() = default;
			ECLIPSE_ENGINE ~OpenGLShaderProgram() override;

			ECLIPSE_ENGINE void CreateProgram() override;
			ECLIPSE_ENGINE void SetVertShader(const IVertexShader& _vertexShader) override;
			ECLIPSE_ENGINE void SetFragShader(const IFragmentShader& _fragmentShader) override;
			ECLIPSE_ENGINE void Link() override;
			ECLIPSE_ENGINE void LinkVertFragShader(const IVertexShader& _vertexShader, const IFragmentShader& _fragmentShader) override;
			ECLIPSE_ENGINE int GetProgram() const override;
			ECLIPSE_ENGINE void Bind() override;
			ECLIPSE_ENGINE void Unbind() override;
			ECLIPSE_ENGINE void Delete() override;

			ECLIPSE_ENGINE void SetTexture2D(const char* _uniformName, int _textureID) override;
			ECLIPSE_ENGINE void SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose = false) override;

		private:
			GLuint m_shaderProgramID = GL_NONE;
		};
	}
}