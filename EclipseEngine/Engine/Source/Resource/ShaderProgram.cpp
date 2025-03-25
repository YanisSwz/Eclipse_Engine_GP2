#include "Resource/ShaderProgram.hpp"

namespace Resource
{

	ShaderProgram::ShaderProgram()
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		Delete();
	}

	void ShaderProgram::GetContentFile()
	{
		return;
	}

	bool ShaderProgram::SetVertFragShader(Resource::VertShader* _vertShader, Resource::FragShader* _fragShader)
	{
		m_vertShader = _vertShader;
		m_fragShader = _fragShader;
		return (m_vertShader->IsLoaded() && m_fragShader->IsLoaded());
	}

	void ShaderProgram::Generate(RHI::IRenderInterface* _rdrInterface)
	{
		m_rdrInter = _rdrInterface;
		m_shaderProgram = m_rdrInter->InstantiateShaderProgram();
		m_shaderProgram->CreateProgram();
		m_shaderProgram->LinkVertFragShader(m_vertShader->GetID(), m_fragShader->GetID());

		bIsLoaded = true;
	}

	void ShaderProgram::Delete()
	{
		m_shaderProgram->Delete();
		m_vertShader = nullptr;
		m_fragShader = nullptr;
	}

	void ShaderProgram::Bind()
	{
		m_shaderProgram->Bind();
	}

	void ShaderProgram::Unbind()
	{
		m_shaderProgram->Unbind();
	}

	void ShaderProgram::SetInt(const char* _uniformName, int _value)
	{
		m_shaderProgram->SetInt(_uniformName, _value);
	}

	void ShaderProgram::SetFloat(const char* _uniformName, float _value)
	{
		m_shaderProgram->SetFloat(_uniformName, _value);
	}

	void ShaderProgram::SetVec3(const char* _uniformName, Math::Vec3 _vec3)
	{
		m_shaderProgram->SetVec3(_uniformName, _vec3);
	}

	void ShaderProgram::SetVec4(const char* _uniformName, Math::Vec4 _vec4)
	{
		m_shaderProgram->SetVec4(_uniformName, _vec4);
	}

	void ShaderProgram::SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose)
	{
		m_shaderProgram->SetMat4(_uniformName, _mat4, _transpose);
	}

	void ShaderProgram::SetTexture2D(const char* _uniformName, int _textureID)
	{
		m_shaderProgram->SetTexture2D(_uniformName, _textureID);
	}
}