#pragma once
#include "RHIInterfaces/IRenderPass/IRenderPass.hpp"

namespace RHI::OpenGL
{
	class OpenGLRenderPass : public RHI::IRenderPass
	{
	public:
		OpenGLRenderPass() = default;
		virtual ~OpenGLRenderPass() override = default;

		virtual void Init(int _width, int _height) override = 0;
		virtual void Rescale(int _width, int _height) override = 0;
		virtual void Delete() override = 0;

	private:
	};
}