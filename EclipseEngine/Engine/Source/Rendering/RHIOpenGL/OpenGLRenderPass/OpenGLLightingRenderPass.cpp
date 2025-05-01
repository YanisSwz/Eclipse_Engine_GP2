#include "RHIOpenGL/OpenGLRenderPass/OpenGLLightingRenderPass.hpp"
#include "RHIOpenGL/OpenGLFrameBuffer.hpp"
#include "Resource/ResourceManager.hpp"
#include <string>

namespace RHI::OpenGL
{
	OpenGLLightingRenderPass::OpenGLLightingRenderPass()
	{
	}

	OpenGLLightingRenderPass::~OpenGLLightingRenderPass()
	{
		Delete();
	}

	void OpenGLLightingRenderPass::Init(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}

	void OpenGLLightingRenderPass::Rescale(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}

	void OpenGLLightingRenderPass::Delete()
	{
	}

	void OpenGLLightingRenderPass::Draw(Math::Vec3 _viewPos, GLuint _gPosition, GLuint _gNormal, GLuint _gAlbedoSpec, Math::Vec4 _ambientLight, std::vector<RHI::DirLightData> _dirLightsData, std::vector<RHI::PointLightData> _pointLightsData, std::vector<RHI::SpotLightData> _spotLightsData)
	{
		if (!m_shaderLight)
		{
			m_shaderLight = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(m_LightingShaderProgramName);
			if (!m_shaderLight)
				return;
		}

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shaderLight->Bind();
		m_shaderLight->SetInt("gPosition", 0);
		m_shaderLight->SetInt("gNormal", 1);
		m_shaderLight->SetInt("gAlbedoSpec", 2);
		m_shaderLight->SetVec3("viewPos", _viewPos);
		m_shaderLight->SetVec4("ambient", _ambientLight);

		SetDirLights(_dirLightsData);
		SetPointLights(_pointLightsData);
		SetSpotLights(_spotLightsData);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _gPosition);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _gNormal);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		m_shaderLight->Unbind();
	}

	void OpenGLLightingRenderPass::SetDirLights(std::vector<RHI::DirLightData> _dirLightsData)
	{
		if (m_shaderLight != nullptr)
		{
			for (int i = 0; i < _dirLightsData.size(); ++i)
			{
				std::string str = "dirLights[" + std::to_string(i) + "].";
				m_shaderLight->SetVec4((str + "Color").c_str(), _dirLightsData[i].color);
				m_shaderLight->SetVec3((str + "Direction").c_str(), _dirLightsData[i].dir);
				m_shaderLight->SetFloat((str + "Padding").c_str(), _dirLightsData[i].padding);
			}
			m_shaderLight->SetInt("DirLightNb", static_cast<int>(_dirLightsData.size()));
		}
	}

	void OpenGLLightingRenderPass::SetPointLights(std::vector<RHI::PointLightData> _pointLightsData)
	{
		if (m_shaderLight != nullptr)
		{
			for (int i = 0; i < _pointLightsData.size(); ++i)
			{
				std::string str = "pointLights[" + std::to_string(i) + "].";
				m_shaderLight->SetVec4((str + "Color").c_str(), _pointLightsData[i].color);
				m_shaderLight->SetVec3((str + "Position").c_str(), _pointLightsData[i].pos);
				m_shaderLight->SetFloat((str + "ConstantAttenuation").c_str(), _pointLightsData[i].constAttenuation);
				m_shaderLight->SetFloat((str + "LinearAttenuation").c_str(), _pointLightsData[i].linAttenuation);
				m_shaderLight->SetFloat((str + "QuadraticAttenuation").c_str(), _pointLightsData[i].quadAttenuation);
				m_shaderLight->SetFloat((str + "Padding1").c_str(), _pointLightsData[i].padding1);
				m_shaderLight->SetFloat((str + "Padding2").c_str(), _pointLightsData[i].padding2);
			}
			m_shaderLight->SetInt("PointLightNb", static_cast<int>(_pointLightsData.size()));
		}
	}

	void OpenGLLightingRenderPass::SetSpotLights(std::vector<RHI::SpotLightData> _spotLightsData)
	{
		if (m_shaderLight != nullptr)
		{
			for (int i = 0; i < _spotLightsData.size(); ++i)
			{
				std::string str = "spotLights[" + std::to_string(i) + "].";
				m_shaderLight->SetVec4((str + "Color").c_str(), _spotLightsData[i].color);
				m_shaderLight->SetVec3((str + "Position").c_str(), _spotLightsData[i].pos);
				m_shaderLight->SetFloat((str + "InnerCutoff").c_str(), _spotLightsData[i].innerCutOff);
				m_shaderLight->SetVec3((str + "Direction").c_str(), _spotLightsData[i].dir);
				m_shaderLight->SetFloat((str + "OuterCutoff").c_str(), _spotLightsData[i].outerCutOff);
				m_shaderLight->SetFloat((str + "ConstantAttenuation").c_str(), _spotLightsData[i].constAttenuation);
				m_shaderLight->SetFloat((str + "LinearAttenuation").c_str(), _spotLightsData[i].linAttenuation);
				m_shaderLight->SetFloat((str + "QuadraticAttenuation").c_str(), _spotLightsData[i].quadAttenuation);
				m_shaderLight->SetFloat((str + "Padding").c_str(), _spotLightsData[i].padding);
			}
			m_shaderLight->SetInt("SpotLightNb", static_cast<int>(_spotLightsData.size()));
		}
	}
}