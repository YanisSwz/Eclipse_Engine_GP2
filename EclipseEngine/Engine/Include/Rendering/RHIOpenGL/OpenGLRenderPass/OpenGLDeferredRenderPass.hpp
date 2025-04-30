#pragma once
#include "RHIOpenGL/OpenGLRenderPass/OpenGLRenderPass.hpp"
#include <glad/glad.h>

namespace RHI::OpenGL
{
	class OpenGLDeferredRenderPass : public OpenGLRenderPass
	{
	public:
		OpenGLDeferredRenderPass();
		~OpenGLDeferredRenderPass() override;

		GLuint gPosition;
		GLuint gNormal;
		GLuint gAlbedoSpec;
		GLuint rboDepth;
		GLuint gBuffer;

		void Init(int _width, int _height) override;
		void Rescale(int _width, int _height) override;
		void Delete() override;

		void Bind();
		void Unbind();

	private:
	};
}