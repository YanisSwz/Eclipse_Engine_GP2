#include "RHIOpenGL/OpenGLRenderPass/OpenGLLightingRenderPass.hpp"
#include "RHIOpenGL/OpenGLFrameBuffer.hpp"
#include "Resource/ResourceManager.hpp"


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

	void OpenGLLightingRenderPass::Draw(Math::Vec3 _viewPos, OpenGLFrameBuffer* _finalFB, GLuint _gPosition, GLuint _gNormal, GLuint _gAlbedoSpec)
	{
		if (!m_shaderLight)
		{
			m_shaderLight = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(m_LightingShaderProgramName);
			if (!m_shaderLight)
				return;
		}

		_finalFB->Bind();
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shaderLight->Bind();
		m_shaderLight->SetInt("gPosition", 0);
		m_shaderLight->SetInt("gNormal", 1);
		m_shaderLight->SetInt("gAlbedoSpec", 2);
		m_shaderLight->SetVec3("viewPos", _viewPos);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _gPosition);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _gNormal);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		m_shaderLight->Unbind();
		_finalFB->Unbind();
	}
}