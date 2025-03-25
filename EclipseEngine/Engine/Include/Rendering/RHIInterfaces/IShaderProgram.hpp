#pragma once
#include "Maths.hpp"

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
		virtual void SetVertShader(unsigned int _vertShaderID) = 0;
		virtual void SetFragShader(unsigned int _fragShaderID) = 0;
		virtual void Link() = 0;
		virtual void LinkVertFragShader(unsigned int _vertShaderID, unsigned int _fragShaderID) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual int GetProgram() const = 0;
		virtual void Delete() = 0;

		virtual void SetInt(const char* _uniformName, int _value) = 0;
		virtual void SetFloat(const char* _uniformName, float _value) = 0;
		virtual void SetVec3(const char* _uniformName, Math::Vec3 _vec3) = 0;
		virtual void SetVec4(const char* _uniformName, Math::Vec4 _vec4) = 0;
		virtual void SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose = false) = 0;
		virtual void SetTexture2D(const char* _uniformName, int _textureID) = 0;

	private:
	};
}