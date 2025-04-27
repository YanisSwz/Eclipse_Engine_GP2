#pragma once
#include "RHIOpenGL/OpenGLRenderPass/OpenGLRenderPass.hpp"
#include "Maths.hpp"

namespace Resource
{
	class Skybox;
	class ShaderProgram;
}

namespace RHI::OpenGL
{
	class OpenGLSkyboxRenderPass : public OpenGLRenderPass
	{
	public:
		OpenGLSkyboxRenderPass();
		~OpenGLSkyboxRenderPass();

		void Init(int _width, int _height) override;
		void Rescale(int _width, int _height) override;
		void Delete() override;

		void Draw(Math::Mat4 _VP);

	private:
		Resource::ShaderProgram* m_shaderProgram = nullptr;
		Resource::Skybox* m_skybox = nullptr;
		bool bisSkyboxEnable = true;

	};
}