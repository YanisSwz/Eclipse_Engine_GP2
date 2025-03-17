#pragma once
#include "Mat4.hpp"

namespace RHI
{
	class IVertexShader;
	class IFragmentShader;

	class IShaderProgram
	{
	public:
		IShaderProgram() = default;
		virtual ~IShaderProgram() = default;

		virtual void CreateProgram() = 0;
		virtual void SetVertShader(const IVertexShader& _vertexShader) = 0;
		virtual void SetFragShader(const IFragmentShader& _fragmentShader) = 0;
		virtual void Link() = 0;
		virtual void LinkVertFragShader(const IVertexShader& _vertexShaderconst, const IFragmentShader& _fragmentShader) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual int GetProgram() const = 0;
		virtual void Delete() = 0;

		virtual void SetTexture2D(const char* _uniformName, int _textureID) = 0;
		virtual void SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose = false) = 0;

	private:

	};
}