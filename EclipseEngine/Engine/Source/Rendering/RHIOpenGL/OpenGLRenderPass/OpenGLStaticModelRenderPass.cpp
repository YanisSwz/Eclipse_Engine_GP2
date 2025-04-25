#include "RHIOpenGL/OpenGLRenderPass/OpenGLStaticModelRenderPass.hpp"

namespace RHI::OpenGL
{
	OpenGLStaticModelRenderPass::OpenGLStaticModelRenderPass()
	{
	}

	OpenGLStaticModelRenderPass::~OpenGLStaticModelRenderPass()
	{
	}

	void OpenGLStaticModelRenderPass::Init(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}

	void OpenGLStaticModelRenderPass::Rescale(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}

	void OpenGLStaticModelRenderPass::Delete()
	{

	}

	void OpenGLStaticModelRenderPass::Draw(Math::Mat4 _VP, std::vector<Resource::ModelData> _models) const
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (Resource::ModelData modelData : _models)
		{
			modelData.shaderProgram->Bind();
			modelData.shaderProgram->SetMat4("VP", _VP, true);
			modelData.shaderProgram->SetMat4("TRS", modelData.TRS, true);
			modelData.texture->Bind();
			modelData.mesh->Draw();
			modelData.texture->Unbind();
			modelData.shaderProgram->Unbind();
		}
	}
}