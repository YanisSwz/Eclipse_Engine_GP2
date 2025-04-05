#include "RHIInterfaces/IRenderInterface.hpp"
#include "RHIOpenGL/OpenGLRenderInterface.hpp"
#include "GLFWWindow.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "SceneCamera.hpp"
#include "Resource/Texture.hpp"
#include "Resource/Model.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Resource/Skybox.hpp"
#include "Resource/ResourceManager.hpp"
#include <iostream>
#define ImGuiImplementGLFW
#define ImGuiImplementOpenGL

int main()
{
	Windowing::IWindow* window = new Windowing::GLFWWindow;
	window->CreateWindow("Eclipse Engine", 1280, 720);

	RHI::IRenderInterface* rdrInter = new RHI::OpenGL::OpenGLRenderInterface;

	if (!rdrInter->InitGraphicsAPI())
	{
		window->DestroyWindow();
		return -1;
	}
	
	rdrInter->EnableContextCapability(RHI::IFLAGS::DEPTH_TEST);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

#ifdef ImGuiImplementGLFW
	ImGui_ImplGlfw_InitForOpenGL(window->CastGLFW()->GetWindow(), true);
#endif // ImGuiImplementGLFW

#ifdef ImGuiImplementOpenGL
	ImGui_ImplOpenGL3_Init("#version 330");
#endif // ImGuiImplementOpenGL

	Resource::Model* model = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Model>("VikingRoom.obj", "Assets/Models/VikingRoom.obj");
	Resource::Texture* texture = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("VikingRoom.img", "Assets/Textures/VikingRoom.png");
	Resource::VertShader* vertShader = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("VertShader.vert", "Assets/Shaders/Default/Default.vert");
	Resource::FragShader* fragShader = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("FragShader.frag", "Assets/Shaders/Default/Default.frag");
	Resource::ShaderProgram* shaderProgram = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("ShaderProgram.shd", "VertShader.vert", "FragShader.frag");

	Resource::Skybox* skybox = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Skybox>("Skybox.skb", "Assets/Skybox/Default", "Cube.obj", "ShaderProgramSkybox.shd");
	Resource::Model* modelSkybox = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Model>("Cube.obj", "Assets/Models/Cube.obj");
	Resource::VertShader* vertShaderSkybox = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("VertShaderSkybox.vert", "Assets/Shaders/Skybox/SkyboxShader.vert");
	Resource::FragShader* fragShaderSkybox = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("FragShaderSkybox.frag", "Assets/Shaders/Skybox/SkyboxShader.frag");
	Resource::ShaderProgram* shaderProgramSkybox = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("ShaderProgramSkybox.shd", "VertShaderSkybox.vert", "FragShaderSkybox.frag");
	
	// Load Shader for default graphic pipeline
	Resource::VertShader* vertShaderDeferredRendering = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("DefaultDeferredRendering.vert", "Assets/Shaders/DeferredRendering/DefaultDeferredRendering.vert");
	Resource::FragShader* fragShaderDeferredRendering = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("DefaultDeferredRendering.frag", "Assets/Shaders/DeferredRendering/DefaultDeferredRendering.frag");
	Resource::ShaderProgram* shaderProgramDeferredRendering = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("DefaultDeferredRendering.shd", "DefaultDeferredRendering.vert", "DefaultDeferredRendering.frag");

	Resource::VertShader* vertShaderDeferredLighting = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("DeferredLighting.vert", "Assets/Shaders/DeferredRendering/DeferredLighting.vert");
	Resource::FragShader* fragShaderDeferredLighting = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("DeferredLighting.frag", "Assets/Shaders/DeferredRendering/DeferredLighting.frag");
	Resource::ShaderProgram* shaderProgramDeferredLighting = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("DeferredLighting.shd", "DeferredLighting.vert", "DeferredLighting.frag");

	Resource::ResourceManager::GetInstance().LoadAllResources();
	Resource::ResourceManager::GetInstance().GenerateAllResources(rdrInter);



	Core::SceneCamera sceneCamera{ 60.f, 0.1f, 100.f };
	RHI::IGraphicPipeline* defaultPipeline = rdrInter->InstantiateDefaultGraphicPipeline();
	
	defaultPipeline->Init(window->width, window->height);

	float deltaTime = 0.f;
	float oldTime = 0.f;
	float crtAngle = 0.f;
	float speed = 1.f;
	Math::Mat4 TRS;
	
	while (!window->WindowShouldClose())
	{
		window->UpdateInputs();
		if (window->GetKey(Windowing::KEY_CODE::KEY_ESCAPE, Windowing::INPUT_ACTION::INPUT_PRESS))
			window->SetWindowShouldClose(true);

		// Update Delta Time and Model rotation
		deltaTime = window->GetTime() - oldTime;
		oldTime = window->GetTime();
		crtAngle += (deltaTime * speed);

#ifdef ImGuiImplementOpenGL
		ImGui_ImplOpenGL3_NewFrame();
#endif // ImGuiImplementOpenGL

#ifdef ImGuiImplementGLFW
		ImGui_ImplGlfw_NewFrame();
#endif // ImGuiImplementGLFW
		ImGui::NewFrame();

		// SCENE WINDOW
		ImGui::Begin("Scene");
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 windowPos = ImGui::GetWindowPos();
		sceneCamera.Update(window, deltaTime, { 0.f, 0.f }, { windowSize.x, windowSize.y });

		defaultPipeline->Rescale(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
		rdrInter->Viewport(0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));

		ImGui::GetWindowDrawList()->AddImage(
			(intptr_t)(defaultPipeline->GetFinalTexture()),
			ImVec2(windowPos.x, windowPos.y),
			ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
			ImVec2(0, 1),
			ImVec2(1, 0));

		ImGui::End();
		ImGui::Render();

		rdrInter->ClearBackgroundColor({ 1, 0.064f, 0.941f });
		rdrInter->ClearBuffer(RHI::IFLAGS::COLOR_BUFFER_BIT);
		rdrInter->ClearBuffer(RHI::IFLAGS::DEPTH_BUFFER_BIT);

		defaultPipeline->Draw(sceneCamera.GetVP(), sceneCamera.GetViewPos());

#ifdef ImGuiImplementOpenGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif // ImGuiImplementOpenGL

		window->SwapBuffers();
		window->PollEvents();
	}

	rdrInter->DestroyDefaultGraphicPipeline(defaultPipeline);

	delete model; // TODO Remove rdrInter->Destroy from Delete
	delete texture; // TODO Remove rdrInter->Destroy from Delete
	delete vertShader; // TODO Remove rdrInter->Destroy from Delete
	delete fragShader; // TODO Remove rdrInter->Destroy from Delete
	delete shaderProgram; // TODO Remove rdrInter->Destroy from Delete
	delete modelSkybox; // TODO Remove rdrInter->Destroy from Delete
	delete vertShaderSkybox; // TODO Remove rdrInter->Destroy from Delete
	delete fragShaderSkybox; // TODO Remove rdrInter->Destroy from Delete
	delete shaderProgramSkybox; // TODO Remove rdrInter->Destroy from Delete
	delete skybox; // TODO Remove rdrInter->Destroy from Delete
	delete vertShaderDeferredRendering; // TODO Remove rdrInter->Destroy from Delete
	delete fragShaderDeferredRendering; // TODO Remove rdrInter->Destroy from Delete
	delete shaderProgramDeferredRendering; // TODO Remove rdrInter->Destroy from Delete
	delete vertShaderDeferredLighting; // TODO Remove rdrInter->Destroy from Delete
	delete fragShaderDeferredLighting; // TODO Remove rdrInter->Destroy from Delete
	delete shaderProgramDeferredLighting; // TODO Remove rdrInter->Destroy from Delete
	Resource::ResourceManager::GetInstance().DestroyInstance();

#pragma region Destroy ImGUI
#ifdef ImGuiImplementOpenGL
	ImGui_ImplOpenGL3_Shutdown();
#endif // ImGuiImplementOpenGL

#ifdef ImGuiImplementGLFW
	ImGui_ImplGlfw_Shutdown();
#endif // ImGuiImplementGLFW

	ImGui::DestroyContext();
#pragma endregion

	window->DestroyWindow();

	delete rdrInter;
	delete window;
	return 0;
}

