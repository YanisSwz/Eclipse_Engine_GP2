#pragma once
#include "RHIInterfaces/IShaderProgram.hpp"
#include "Resource/VertShader.hpp"
#include "Resource/FragShader.hpp"
#include "Resource/GeoShader.hpp"
#include "IResource.hpp"
#include "Maths.hpp"

namespace Resource
{
	class ShaderProgram : public IGraphicsResource
	{
	public:
		ECLIPSE_ENGINE ShaderProgram(std::string _name = "");
		ECLIPSE_ENGINE ~ShaderProgram() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path) override;
		ECLIPSE_ENGINE void SetVertFragShader(std::string _vertShaderName, std::string _fragShaderName);
		ECLIPSE_ENGINE void SetVertGeoFragShader(std::string _vertShaderName, std::string _fragShaderName, std::string _geoShader);
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;

		ECLIPSE_ENGINE void Delete() override;

		ECLIPSE_ENGINE void Bind();
		ECLIPSE_ENGINE void Unbind();
		ECLIPSE_ENGINE int GetProgramID() const;
		

		ECLIPSE_ENGINE void SetInt(const char* _uniformName, int _value);
		ECLIPSE_ENGINE void SetFloat(const char* _uniformName, float _value);
		ECLIPSE_ENGINE void SetVec3(const char* _uniformName, Math::Vec3 _vec3);
		ECLIPSE_ENGINE void SetVec4(const char* _uniformName, Math::Vec4 _vec4);
		ECLIPSE_ENGINE void SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose = false);
		ECLIPSE_ENGINE void SetTexture2D(const char* _uniformName, int _textureID);

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		RHI::IShaderProgram* m_shaderProgram = nullptr;

		Resource::VertShader* m_vertShader = nullptr;
		Resource::FragShader* m_fragShader = nullptr;
		Resource::GeoShader* m_geoShader = nullptr;
		std::string m_vertShaderName = "";
		std::string m_fragShaderName = "";
		std::string m_geoShaderName = "";
	};
}