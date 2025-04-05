#include "RHIOpenGL/OpenGLPipeline/OpenGLDefaultGraphicPipeline.hpp"
#include "Maths.hpp"
#include <iostream>

#include "Resource/ResourceManager.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Resource/Model.hpp"
#include "Resource/Texture.hpp"

namespace RHI::OpenGL
{
	OpenGLDefaultGraphicPipeline::OpenGLDefaultGraphicPipeline()
	{
		m_FB = new OpenGLFrameBuffer;
		m_deferredRenderPass = new OpenGLDeferredRenderPass;
		m_lightingRenderPass = new OpenGLLightingRenderPass;
	}

	OpenGLDefaultGraphicPipeline::~OpenGLDefaultGraphicPipeline()
	{
		Delete();
	}

	void OpenGLDefaultGraphicPipeline::Init(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;

		m_FB->Init(_width, _height);
		m_deferredRenderPass->Init(m_width, m_height);
		m_lightingRenderPass->Init(m_width, m_height);
	}

	void OpenGLDefaultGraphicPipeline::Rescale(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;

		m_FB->Rescale(m_width, m_height);
		m_deferredRenderPass->Rescale(m_width, m_height);
		m_lightingRenderPass->Rescale(m_width, m_height);
	}

	void OpenGLDefaultGraphicPipeline::Delete()
	{
		delete m_deferredRenderPass;
		delete m_lightingRenderPass;
		delete m_FB;
	}

	void OpenGLDefaultGraphicPipeline::Draw(Math::Mat4 _VP, Math::Vec3 _viewPos)
	{
		// Deferred Render Pass
		m_deferredRenderPass->Bind();

		// Static / Dynamic Mesh Render Pass
		m_deferredShaderProgram = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(m_DeferredShaderProgramName);
		if (!m_deferredShaderProgram)
		{
			m_deferredShaderProgram = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(m_DeferredShaderProgramName);
			if (!m_deferredShaderProgram)
				return;
		}

		Resource::Model* model = Resource::ResourceManager::GetInstance().GetResource<Resource::Model>("VikingRoom.obj");
		Resource::Texture* texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("VikingRoom.img");
		if (!model || !texture)
			return;

		Math::Mat4 TRS = Math::Mat4::TRS(Math::Vec3{ 0.f, 0.f, 0.f }, Math::Vec3{ 0.f, 0.f, 0.f }, Math::Vec3{ 1.f, 1.f, 1.f });

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_deferredShaderProgram->Bind();
		m_deferredShaderProgram->SetMat4("TRS", TRS, false);
		m_deferredShaderProgram->SetMat4("VP", _VP, true);
		texture->Bind();
		model->Draw();
		texture->Unbind();
		m_deferredShaderProgram->Unbind();

		m_deferredRenderPass->Unbind();

		// Lighting Render Pass
		m_lightingRenderPass->Draw(_viewPos, m_FB, m_deferredRenderPass->gPosition, m_deferredRenderPass->gNormal, m_deferredRenderPass->gAlbedoSpec);
	}

	unsigned int OpenGLDefaultGraphicPipeline::GetFinalTexture() const
	{
		return m_FB->GetTextureID();
	}
}