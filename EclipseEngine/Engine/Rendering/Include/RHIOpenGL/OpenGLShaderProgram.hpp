#pragma once
#include "RHIInterfaces/IShaderProgram.hpp"
#include "Maths.hpp"
#include <string>

class Mat4; // TODO Remove

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLShaderProgram : public IShaderProgram
		{
		public:
			OpenGLShaderProgram() = default;
			~OpenGLShaderProgram() override;

			void CreateProgram() override;
			void SetVertShader(const IVertexShader& _vertexShader) override;
			void SetFragShader(const IFragmentShader& _fragmentShader) override;
			void Link() override;
			void LinkVertFragShader(const IVertexShader& _vertexShader, const IFragmentShader& _fragmentShader) override;
			int GetProgram() const override;
			void Bind() override;
			void Unbind() override;
			void Delete() override;

			void SetTexture2D(const char* _uniformName, int _textureID) override;
			void SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose = false) override;

		private:
			GLuint shaderProgramID = GL_NONE;
		};
	}
}