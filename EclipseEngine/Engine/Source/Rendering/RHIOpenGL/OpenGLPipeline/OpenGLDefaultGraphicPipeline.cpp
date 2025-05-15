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
		m_particleRenderPass = new OpenGLParticleRenderPass;
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
		m_particleRenderPass->Init(m_width, m_height);
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
		m_particleRenderPass->Rescale(m_width, m_height);
	}

	void OpenGLDefaultGraphicPipeline::Delete()
	{
		delete m_deferredRenderPass;
		delete m_skyboxRenderPass;
		delete m_staticModelRenderPass;
		delete m_lightingRenderPass;
		delete m_particleRenderPass;
		delete m_FB;
	}

	int OpenGLDefaultGraphicPipeline::PickObjectID(int _mousePosX, int _mousePosY)
	{
		return m_deferredRenderPass->PickID(_mousePosX, _mousePosY);
	}

	void OpenGLDefaultGraphicPipeline::Draw(Math::Mat4 _V, Math::Mat4 _P, Math::Vec3 _viewPos, std::vector<Resource::ModelData> _staticModels, Math::Vec4 _ambientLight, std::vector<RHI::DirLightData> _dirLights, std::vector<RHI::PointLightData> _pointLights, std::vector<RHI::SpotLightData> _spotLights, std::vector<Core::ParticleEmitterRenderData> _particlesData)
	{
		Math::Mat4 _VP = _P * _V;

		// Deferred Render Pass
		m_deferredRenderPass->Bind();

		glClearColor(m_backgroundColor.x, m_backgroundColor.y, m_backgroundColor.z, m_backgroundColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_skyboxRenderPass->Draw(_VP);
		// Static Mesh Render Pass
		m_staticModelRenderPass->Draw(_VP, _staticModels);
		m_deferredRenderPass->Unbind();
		
		// Lighting Render Pass
		m_FB->Bind();
		m_lightingRenderPass->Draw(_viewPos, m_deferredRenderPass->gPosition, m_deferredRenderPass->gNormal, m_deferredRenderPass->gAlbedoSpec, _ambientLight, _dirLights, _pointLights, _spotLights);
		m_FB->Unbind();

		// Copy Deferred depth buffer into final framebuffer depth buffer
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_deferredRenderPass->gBuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FB->GetFrameBufferID()); // write to default framebuffer
		glBlitFramebuffer(0, 0, m_deferredRenderPass->GetWidth(), m_deferredRenderPass->GetHeight(), 0, 0, m_FB->width, m_FB->height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Particle Render Pass
		m_FB->Bind();
		m_particleRenderPass->Draw(_V, _P, _particlesData);
		m_FB->Unbind();
	}

	unsigned int OpenGLDefaultGraphicPipeline::GetFinalTexture() const
	{
		return m_FB->GetTextureID();
	}
}