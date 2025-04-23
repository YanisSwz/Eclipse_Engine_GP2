#include "RHIOpenGL/OpenGLPipeline/OpenGLDefaultGraphicPipeline.hpp"

namespace RHI::OpenGL
{
	OpenGLDefaultGraphicPipeline::OpenGLDefaultGraphicPipeline()
	{
		m_FB = new OpenGLFrameBuffer;
		m_deferredRenderPass = new OpenGLDeferredRenderPass;
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
		m_staticModelRenderPass->Init(m_width, m_height);
		m_lightingRenderPass->Init(m_width, m_height);
	}

	void OpenGLDefaultGraphicPipeline::Rescale(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;

		m_FB->Rescale(m_width, m_height);
		m_deferredRenderPass->Rescale(m_width, m_height);
		m_staticModelRenderPass->Rescale(m_width, m_height);
		m_lightingRenderPass->Rescale(m_width, m_height);
	}

	void OpenGLDefaultGraphicPipeline::Delete()
	{
		delete m_deferredRenderPass;
		delete m_staticModelRenderPass;
		delete m_lightingRenderPass;
		delete m_FB;
	}

	void OpenGLDefaultGraphicPipeline::Draw(Math::Mat4 _VP, Math::Vec3 _viewPos, std::vector<Resource::ModelData> _staticModels, std::vector<RHI::DirLightData> _dirLights, std::vector<RHI::PointLightData> _pointLights, std::vector<RHI::SpotLightData> _spotLights)
	{
		// Deferred Render Pass
		m_deferredRenderPass->Bind();

		// Static Mesh Render Pass
		m_staticModelRenderPass->Draw(_VP, _staticModels);

		// Lighting Render Pass
		m_deferredRenderPass->Unbind();
		m_lightingRenderPass->Draw(_viewPos, m_FB, m_deferredRenderPass->gPosition, m_deferredRenderPass->gNormal, m_deferredRenderPass->gAlbedoSpec, _dirLights, _pointLights, _spotLights);
	}

	unsigned int OpenGLDefaultGraphicPipeline::GetFinalTexture() const
	{
		return m_FB->GetTextureID();
	}
}