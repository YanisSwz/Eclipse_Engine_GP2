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
			ECLIPSE_ENGINE void SetVertShader(unsigned int _vertShaderID) override;
			ECLIPSE_ENGINE void SetFragShader(unsigned int _fragShaderID) override;
			ECLIPSE_ENGINE void Link() override;
			ECLIPSE_ENGINE void LinkVertFragShader(unsigned int _vertShaderID, unsigned int _fragShaderID) override;
			ECLIPSE_ENGINE void LinkVertGeoFragShader(unsigned int _vertShaderID, unsigned int _fragShaderID, unsigned int _geoShaderID) override;
			ECLIPSE_ENGINE int GetProgram() const override;
			ECLIPSE_ENGINE void Bind() override;
			ECLIPSE_ENGINE void Unbind() override;
			ECLIPSE_ENGINE void Delete() override;

			ECLIPSE_ENGINE void SetInt(const char* _uniformName, int _value) override;
			ECLIPSE_ENGINE void SetFloat(const char* _uniformName, float _value) override;
			ECLIPSE_ENGINE void SetVec3(const char* _uniformName, Math::Vec3 _vec3) override;
			ECLIPSE_ENGINE void SetVec4(const char* _uniformName, Math::Vec4 _vec4) override;
			ECLIPSE_ENGINE void SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose = false) override;
			ECLIPSE_ENGINE void SetTexture2D(const char* _uniformName, int _textureID) override;

		private:
			GLuint m_shaderProgramID = GL_NONE;
		};
	}
}