#include "RHIOpenGL/OpenGLRenderPass/OpenGLSkyboxRenderPass.hpp"
#include "Resource/Skybox.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Resource/ResourceManager.hpp"

namespace RHI::OpenGL
{
	OpenGLSkyboxRenderPass::OpenGLSkyboxRenderPass()
	{
	}

	OpenGLSkyboxRenderPass::~OpenGLSkyboxRenderPass()
	{
	}

	void OpenGLSkyboxRenderPass::Init(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}

	void OpenGLSkyboxRenderPass::Rescale(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}

	void OpenGLSkyboxRenderPass::Delete()
	{

	}

	void OpenGLSkyboxRenderPass::Draw(Math::Mat4 _VP)
	{
		if (!bisSkyboxEnable)
			return;

		if (!m_shaderProgram)
			m_shaderProgram = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>("SkyboxShader.shd");

		if (!m_skybox)
			m_skybox = Resource::ResourceManager::GetInstance().GetResource<Resource::Skybox>("Space.skb");

		if (!m_shaderProgram || !m_skybox)
			return;

		m_shaderProgram->Bind();
		m_shaderProgram->SetMat4("VP", _VP, true);
		m_skybox->Draw();
		m_shaderProgram->Unbind();
	}
}