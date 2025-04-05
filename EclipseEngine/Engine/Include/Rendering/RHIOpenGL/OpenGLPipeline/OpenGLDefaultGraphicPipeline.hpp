#pragma once
#include "RHIOpenGL/OpenGLPipeline/OpenGLGraphicPipeline.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLDeferredRenderPass.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLLightingRenderPass.hpp"
#include "RHIOpenGL/OpenGLFrameBuffer.hpp"

namespace RHI::OpenGL
{
	class OpenGLDefaultGraphicPipeline : public OpenGLGraphicPipeline
	{
	public:
		OpenGLDefaultGraphicPipeline();
		~OpenGLDefaultGraphicPipeline() override;

		void Init(int _width, int _height) override;
		void Rescale(int _width, int _height) override;
		void Delete() override;

		void Draw(Math::Mat4 _VP, Math::Vec3 _viewPos) override;
		unsigned int GetFinalTexture() const override;

	private:
		const char* m_DeferredShaderProgramName = "DefaultDeferredRendering.shd";
		Resource::ShaderProgram* m_deferredShaderProgram = nullptr;

		OpenGLDeferredRenderPass* m_deferredRenderPass = nullptr;
		OpenGLLightingRenderPass* m_lightingRenderPass = nullptr;
		OpenGLFrameBuffer* m_FB = nullptr;
	};
}