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