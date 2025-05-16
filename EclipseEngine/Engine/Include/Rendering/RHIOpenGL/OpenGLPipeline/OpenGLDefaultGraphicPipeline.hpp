#pragma once
#include "RHIOpenGL/OpenGLPipeline/OpenGLGraphicPipeline.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLDeferredRenderPass.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLSkyboxRenderPass.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLStaticModelRenderPass.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLLightingRenderPass.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLParticleRenderPass.hpp"
#include "Particles/ParticleRenderData.hpp"
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

		int PickObjectID(int _mousePosX, int _mousePosY) override;

		void Draw(Math::Mat4 _VP, Math::Vec3 _viewPos, std::vector<Resource::ModelData> _staticModels, RHI::LightsData _lightsData, std::vector<std::vector<Core::ParticleRenderData>> _particlesData) override;
		unsigned int GetFinalTexture() const override;

	private:
		OpenGLDeferredRenderPass* m_deferredRenderPass = nullptr;
		OpenGLSkyboxRenderPass* m_skyboxRenderPass = nullptr;
		OpenGLStaticModelRenderPass* m_staticModelRenderPass = nullptr;
		OpenGLLightingRenderPass* m_lightingRenderPass = nullptr;
		OpenGLParticleRenderPass* m_particleRenderPass = nullptr;
		OpenGLFrameBuffer* m_FB = nullptr;
		
		Math::Vec4 m_backgroundColor{ 0.9f, 0.9f, 1.f, 1.f };
	};
}