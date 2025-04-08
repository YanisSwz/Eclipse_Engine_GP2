#pragma once
#include "RHIOpenGL/OpenGLRenderPass/OpenGLRenderPass.hpp"
#include "Resource/ModelData.hpp"
#include <vector>

namespace RHI::OpenGL
{
	class OpenGLStaticModelRenderPass : public OpenGLRenderPass
	{
	public:
		OpenGLStaticModelRenderPass();
		~OpenGLStaticModelRenderPass() override;

		void Init(int _width, int _height) override = 0;
		void Rescale(int _width, int _height) override = 0;
		void Delete() override = 0;

		void Draw(Math::Mat4 _VP, std::vector<Resource::ModelData> _models) const;

	private:
	};
}