#include "RHIOpenGL/OpenGLRenderPass/OpenGLStaticModelRenderPass.hpp"
#include "Resource/ResourceManager.hpp" // TODO Remove

namespace RHI::OpenGL
{
	OpenGLStaticModelRenderPass::OpenGLStaticModelRenderPass()
	{

	}

	OpenGLStaticModelRenderPass::~OpenGLStaticModelRenderPass()
	{
		Delete();
	}

	void OpenGLStaticModelRenderPass::Init(int _width, int _height)
	{

	}

	void OpenGLStaticModelRenderPass::Rescale(int _width, int _height)
	{

	}

	void OpenGLStaticModelRenderPass::Delete()
	{

	}

	void OpenGLStaticModelRenderPass::Draw(Math::Mat4 _VP, std::vector<Resource::ModelData> _models) const
	{
		// Static / Dynamic Mesh Render Pass
		Resource::ShaderProgram* shaderProgram = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>("DefaultDeferredRendering.shd");
		if (!shaderProgram)
		{
			shaderProgram = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>("DefaultDeferredRendering.shd");
			if (!shaderProgram)
				return;
		}

		Resource::Mesh* mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("VikingRoom.obj");
		Resource::Texture* texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("VikingRoom.img");
		if (!mesh || !texture)
			return;

		Math::Mat4 TRS = Math::Mat4::TRS(Math::Vec3{ 0.f, 0.f, 0.f }, Math::Vec3{ 0.f, 0.f, 0.f }, Math::Vec3{ 1.f, 1.f, 1.f });

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram->Bind();
		shaderProgram->SetMat4("TRS", TRS, false);
		shaderProgram->SetMat4("VP", _VP, true);
		texture->Bind();
		mesh->Draw();
		texture->Unbind();
		shaderProgram->Unbind();
	}
}