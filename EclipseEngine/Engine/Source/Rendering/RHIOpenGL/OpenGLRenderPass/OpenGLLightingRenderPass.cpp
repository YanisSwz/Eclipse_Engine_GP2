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
		m_lightShader = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(m_LightingShaderProgramName);

		glGenBuffers(1, &m_ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(RHI::LightsData), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLLightingRenderPass::Rescale(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}

	void OpenGLLightingRenderPass::Delete()
	{
	}

	void OpenGLLightingRenderPass::Draw(Math::Vec3 _viewPos, GLuint _gPosition, GLuint _gNormal, GLuint _gAlbedoSpec, RHI::LightsData _lightsData)
	{
		if (!m_lightShader)
		{
			m_lightShader = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(m_LightingShaderProgramName);
			if (!m_lightShader)
				return;
		}

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_lightShader->Bind();
		m_lightShader->SetInt("gPosition", 0);
		m_lightShader->SetInt("gNormal", 1);
		m_lightShader->SetInt("gAlbedoSpec", 2);
		m_lightShader->SetVec3("viewPos", _viewPos);

		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		memcpy(p, &_lightsData, sizeof(RHI::LightsData));
		glUnmapBuffer(GL_UNIFORM_BUFFER);

		unsigned int block_index = glGetUniformBlockIndex(m_lightShader->GetProgramID(), "lightsData");
		GLuint binding_point_index = 0;
		glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, m_ubo);
		glUniformBlockBinding(m_lightShader->GetProgramID(), block_index, binding_point_index);

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
		m_lightShader->Unbind();
	}
}