#pragma once
#include "RHIOpenGL/OpenGLRenderPass/OpenGLRenderPass.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Maths.hpp"
#include "RHIInterfaces/Lights.hpp"
#include <vector>
#include <glad/glad.h>

namespace RHI::OpenGL
{
	class OpenGLFrameBuffer;

	class OpenGLLightingRenderPass : public OpenGLRenderPass
	{
	public:
		OpenGLLightingRenderPass();
		~OpenGLLightingRenderPass() override;

		void Init(int _width, int _height) override;
		void Rescale(int _width, int _height) override;
		void Delete() override;

		void Draw(Math::Vec3 _viewPos, GLuint _gPosition, GLuint _gNormal, GLuint _gAlbedoSpec, RHI::LightsData _lightsData);

	private:
		const char* m_LightingShaderProgramName = "DeferredLighting.shd";
		Resource::ShaderProgram* m_lightShader = nullptr;

		GLuint m_ubo = 0;
	};
}