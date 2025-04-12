#include "Resource/ShaderProgram.hpp"
#include "Resource/ResourceManager.hpp"

namespace Resource
{

	ShaderProgram::ShaderProgram(const char* _name)
	{
		name = _name;
	}

	ShaderProgram::~ShaderProgram()
	{
		Delete();
	}

	void ShaderProgram::GetFileContent(std::string _path)
	{
		return;
	}

	void ShaderProgram::SetVertFragShader(std::string _vertShaderName, std::string _fragShaderName)
	{
		m_vertShaderName = _vertShaderName;
		m_fragShaderName = _fragShaderName;
	}

	void ShaderProgram::Generate(RHI::IRenderInterface* _rdrInterface)
	{
		m_rdrInter = _rdrInterface;
		if (!m_vertShader)
			m_vertShader = ResourceManager::GetInstance().GetResource<VertShader>(m_vertShaderName);
		if (!m_fragShader)
			m_fragShader = ResourceManager::GetInstance().GetResource<FragShader>(m_fragShaderName);

		if (!m_vertShader || !m_fragShader)
			return;

		m_shaderProgram = m_rdrInter->InstantiateShaderProgram();
		m_shaderProgram->CreateProgram();
		m_shaderProgram->LinkVertFragShader(m_vertShader->GetID(), m_fragShader->GetID());

		bIsLoaded = true;
	}

	void ShaderProgram::Delete()
	{
		if (!m_shaderProgram)
			return;

		m_shaderProgram->Delete();
		m_rdrInter->DestroyShaderProgram(m_shaderProgram);
		m_vertShader = nullptr;
		m_fragShader = nullptr;
	}

	void ShaderProgram::Bind()
	{
		if (!m_shaderProgram)
			return;

		m_shaderProgram->Bind();
	}

	void ShaderProgram::Unbind()
	{
		if (!m_shaderProgram)
			return;

		m_shaderProgram->Unbind();
	}

	void ShaderProgram::SetInt(const char* _uniformName, int _value)
	{
		if (!m_shaderProgram)
			return;

		m_shaderProgram->SetInt(_uniformName, _value);
	}

	void ShaderProgram::SetFloat(const char* _uniformName, float _value)
	{
		if (!m_shaderProgram)
			return;

		m_shaderProgram->SetFloat(_uniformName, _value);
	}

	void ShaderProgram::SetVec3(const char* _uniformName, Math::Vec3 _vec3)
	{
		if (!m_shaderProgram)
			return;

		m_shaderProgram->SetVec3(_uniformName, _vec3);
	}

	void ShaderProgram::SetVec4(const char* _uniformName, Math::Vec4 _vec4)
	{
		if (!m_shaderProgram)
			return;

		m_shaderProgram->SetVec4(_uniformName, _vec4);
	}

	void ShaderProgram::SetMat4(const char* _uniformName, Math::Mat4 _mat4, bool _transpose)
	{
		if (!m_shaderProgram)
			return;

		m_shaderProgram->SetMat4(_uniformName, _mat4, _transpose);
	}

	void ShaderProgram::SetTexture2D(const char* _uniformName, int _textureID)
	{
		if (!m_shaderProgram)
			return;

		m_shaderProgram->SetTexture2D(_uniformName, _textureID);
	}
}