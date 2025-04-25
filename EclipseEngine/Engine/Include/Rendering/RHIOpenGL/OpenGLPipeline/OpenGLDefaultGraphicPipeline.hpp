#pragma once
#include "RHIOpenGL/OpenGLPipeline/OpenGLGraphicPipeline.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLDeferredRenderPass.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLStaticModelRenderPass.hpp"
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

		void Draw(Math::Mat4 _VP, Math::Vec3 _viewPos, std::vector<Resource::ModelData> _staticModels, Math::Vec4 _ambientLight, std::vector<RHI::DirLightData> _dirLights, std::vector<RHI::PointLightData> _pointLights, std::vector<RHI::SpotLightData> _spotLights) override;
		unsigned int GetFinalTexture() const override;

	private:
		OpenGLDeferredRenderPass* m_deferredRenderPass = nullptr;
		OpenGLStaticModelRenderPass* m_staticModelRenderPass = nullptr;
		OpenGLLightingRenderPass* m_lightingRenderPass = nullptr;
		OpenGLFrameBuffer* m_FB = nullptr;
	};
}