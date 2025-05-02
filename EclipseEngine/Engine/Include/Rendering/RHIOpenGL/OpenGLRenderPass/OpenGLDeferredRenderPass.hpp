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

		GLuint gBuffer;
		GLuint gPosition;
		GLuint gNormal;
		GLuint gAlbedoSpec;
		GLuint gPickID;
		GLuint rboDepth;

		void Init(int _width, int _height) override;
		void Rescale(int _width, int _height) override;
		void Delete() override;

		int PickID(int _mousePosX, int _mousePosY);

		void Bind();
		void Unbind();

	private:
	};
}