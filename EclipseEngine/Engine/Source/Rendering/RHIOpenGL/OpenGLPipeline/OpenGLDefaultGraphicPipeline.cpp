#include "RHIOpenGL/OpenGLPipeline/OpenGLDefaultGraphicPipeline.hpp"

namespace RHI::OpenGL
{
	OpenGLDefaultGraphicPipeline::OpenGLDefaultGraphicPipeline()
	{
		m_FB = new OpenGLFrameBuffer;
		m_deferredRenderPass = new OpenGLDeferredRenderPass;
		m_skyboxRenderPass = new OpenGLSkyboxRenderPass;
		m_staticModelRenderPass = new OpenGLStaticModelRenderPass;
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
		m_skyboxRenderPass->Init(m_width, m_height);
		m_staticModelRenderPass->Init(m_width, m_height);
		m_lightingRenderPass->Init(m_width, m_height);
	}

	void OpenGLDefaultGraphicPipeline::Rescale(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;

		m_FB->Rescale(m_width, m_height);
		m_deferredRenderPass->Rescale(m_width, m_height);
		m_skyboxRenderPass->Rescale(m_width, m_height);
		m_staticModelRenderPass->Rescale(m_width, m_height);
		m_lightingRenderPass->Rescale(m_width, m_height);
	}

	void OpenGLDefaultGraphicPipeline::Delete()
	{
		delete m_deferredRenderPass;
		delete m_skyboxRenderPass;
		delete m_staticModelRenderPass;
		delete m_lightingRenderPass;
		delete m_FB;
	}

	void OpenGLDefaultGraphicPipeline::Draw(Math::Mat4 _VP, Math::Vec3 _viewPos, std::vector<Resource::ModelData> _staticModels, Math::Vec4 _ambientLight, std::vector<RHI::DirLightData> _dirLights, std::vector<RHI::PointLightData> _pointLights, std::vector<RHI::SpotLightData> _spotLights)
	{
		// Deferred Render Pass
		m_deferredRenderPass->Bind();

		glClearColor(m_backgroundColor.x, m_backgroundColor.y, m_backgroundColor.z, m_backgroundColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_skyboxRenderPass->Draw(_VP);
		// Static Mesh Render Pass
		m_staticModelRenderPass->Draw(_VP, _staticModels);

		// Lighting Render Pass
		m_deferredRenderPass->Unbind();
		

		m_FB->Bind();
		m_lightingRenderPass->Draw(_viewPos, m_deferredRenderPass->gPosition, m_deferredRenderPass->gNormal, m_deferredRenderPass->gAlbedoSpec, _ambientLight, _dirLights, _pointLights, _spotLights);
		m_FB->Unbind();

		//glBindFramebuffer(GL_READ_FRAMEBUFFER, m_deferredRenderPass->gBuffer);
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FB->GetFrameBufferID());

		//glBindRenderbuffer(GL_RENDERBUFFER, m_deferredRenderPass->rboDepth);
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_deferredRenderPass->rboDepth);
		//glDrawBuffer(GL_DEPTH_ATTACHMENT);

		//glBindRenderbuffer(GL_RENDERBUFFER, m_FB->GetDepthBufferID());
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT + 1, GL_RENDERBUFFER, m_FB->GetDepthBufferID());
		//glReadBuffer(GL_DEPTH_ATTACHMENT + 1);

		//glBlitFramebuffer(0, 0, m_deferredRenderPass->GetWidth(), m_deferredRenderPass->GetWidth(),
		//	0, 0, m_FB->width, m_FB->height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

		//glBindTexture(GL_TEXTURE_2D, 0);
		//glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	unsigned int OpenGLDefaultGraphicPipeline::GetFinalTexture() const
	{
		return m_FB->GetTextureID();
	}
}