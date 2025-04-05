#pragma once
#include "RHIOpenGL/OpenGLRenderPass/OpenGLRenderPass.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Maths.hpp"
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

		void Draw(Math::Vec3 _viewPos, OpenGLFrameBuffer* _finalFB, GLuint _gPosition, GLuint _gNormal, GLuint _gAlbedoSpec);

	private:
		const char* m_LightingShaderProgramName = "DeferredLighting.shd";
		Resource::ShaderProgram* m_shaderLight = nullptr;
	};
}