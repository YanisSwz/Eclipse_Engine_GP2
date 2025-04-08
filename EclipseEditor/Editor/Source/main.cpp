#include "RHIInterfaces/IRenderInterface.hpp"
#include "RHIOpenGL/OpenGLRenderInterface.hpp"
#include "GLFWWindow.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "SceneCamera.hpp"
#include "Resource/Texture.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Resource/Skybox.hpp"
#include "Resource/ResourceManager.hpp"
#include "Scene.hpp"
#include <iostream>
#define ImGuiImplementGLFW
#define ImGuiImplementOpenGL

int main()
{
#pragma region Init Window
	Windowing::IWindow* window = new Windowing::GLFWWindow;
	window->CreateWindow("Eclipse Engine", 1280, 720);
#pragma endregion

#pragma region Init ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	ImGui::StyleColorsDark();

#ifdef ImGuiImplementGLFW
	ImGui_ImplGlfw_InitForOpenGL(window->CastGLFW()->GetWindow(), true);
#endif // ImGuiImplementGLFW

#ifdef ImGuiImplementOpenGL
	ImGui_ImplOpenGL3_Init("#version 330");
#endif // ImGuiImplementOpenGL
#pragma endregion

#pragma region Init Render Interface
	RHI::IRenderInterface* rdrInter = new RHI::OpenGL::OpenGLRenderInterface;
	if (!rdrInter->InitGraphicsAPI())
	{
		window->DestroyWindow();
		return -1;
	}
	rdrInter->EnableContextCapability(RHI::IFLAGS::DEPTH_TEST);
#pragma endregion

#pragma region Load Resources and Scene
	Resource::Mesh* model = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Mesh>("VikingRoom.obj", "Assets/Models/VikingRoom.obj");
	Resource::Texture* texture = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("VikingRoom.img", "Assets/Textures/VikingRoom.png");
	Resource::VertShader* vertShader = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("VertShader.vert", "Assets/Shaders/Default/Default.vert");
	Resource::FragShader* fragShader = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("FragShader.frag", "Assets/Shaders/Default/Default.frag");
	Resource::ShaderProgram* shaderProgram = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("ShaderProgram.shd", "VertShader.vert", "FragShader.frag");

	Resource::Skybox* skybox = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Skybox>("Skybox.skb", "Assets/Skybox/Default", "Cube.obj", "ShaderProgramSkybox.shd");
	Resource::Mesh* modelSkybox = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Mesh>("Cube.obj", "Assets/Models/Cube.obj");
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

	// CORE TESTS
	Core::Scene scene{};
	scene.CreateGameObject();
	scene.CreateGameObject();
	scene.CreateGameObject();

	scene.DestroyGameObject();
	scene.CreateGameObject();
#pragma endregion

	float deltaTime = 0.f;
	float oldTime = 0.f;

	while (!window->WindowShouldClose())
	{
#pragma region Update
		window->UpdateInputs();
		if (window->GetKey(Windowing::KEY_CODE::KEY_ESCAPE, Windowing::INPUT_ACTION::INPUT_PRESS))
			window->SetWindowShouldClose(true);

		deltaTime = window->GetTime() - oldTime;
		oldTime = window->GetTime();

		scene.Update();

		window->PollEvents();
#pragma endregion

#pragma region Draw ImGui

#pragma region Implement GLFW AND OpenGL
#ifdef ImGuiImplementOpenGL
		ImGui_ImplOpenGL3_NewFrame();
#endif // ImGuiImplementOpenGL
#ifdef ImGuiImplementGLFW
		ImGui_ImplGlfw_NewFrame();
#endif // ImGuiImplementGLFW
		ImGui::NewFrame();
#pragma endregion

		//##################################################################################
		//################################### DOCK SPACE ###################################
		//##################################################################################
#pragma region ImGui Dockspace
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
		

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", 0, window_flags);

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		ImGui::End();
		ImGui::PopStyleVar(3);
#pragma endregion

		ImGuiWindowFlags defaultWindowFlags = ImGuiWindowFlags_None;
		ImGuiWindowFlags inspectorWindowFlags = defaultWindowFlags;
		ImGuiWindowFlags sceneWindowFlags = defaultWindowFlags;
		ImGuiWindowFlags hierarchyWindowFlags = defaultWindowFlags;

		//##################################################################################
		//################################## SCENE WINDOW ##################################
		//##################################################################################
#pragma region ImGui Scene
		ImGui::Begin("Scene", 0, sceneWindowFlags);
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 windowPos = ImGui::GetWindowPos();
		sceneCamera.Update(window, deltaTime, { windowPos.x, windowPos.y }, { windowSize.x, windowSize.y });

		defaultPipeline->Rescale(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
		rdrInter->Viewport(0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));

		ImGui::GetWindowDrawList()->AddImage(
			(intptr_t)(defaultPipeline->GetFinalTexture()),
			ImVec2(windowPos.x, windowPos.y),
			ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
			ImVec2(0, 1),
			ImVec2(1, 0));

		ImGui::End();
#pragma endregion

		//##################################################################################
		//#################################### INSPECTOR ###################################
		//##################################################################################
#pragma region ImGui Inspector
		ImGui::Begin("Inspector", 0, inspectorWindowFlags);
		ImGui::End();
#pragma endregion

		//##################################################################################
		//#################################### HIERARCHY ###################################
		//##################################################################################
#pragma region ImGui Hierarchy
		ImGui::Begin("Hierarchy", 0, hierarchyWindowFlags);
		ImGui::End();
#pragma endregion

		ImGui::EndFrame();
#pragma endregion

#pragma region Draw Scene
		rdrInter->ClearBackgroundColor({ 1, 0.064f, 0.941f });
		rdrInter->ClearBuffer(RHI::IFLAGS::COLOR_BUFFER_BIT);
		rdrInter->ClearBuffer(RHI::IFLAGS::DEPTH_BUFFER_BIT);
		
		defaultPipeline->Draw(sceneCamera.GetVP(), sceneCamera.GetViewPos());
#pragma endregion

#pragma region Render ImGui
		ImGui::Render();

#ifdef ImGuiImplementOpenGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif // ImGuiImplementOpenGL
		
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
		window->SwapBuffers();
#pragma endregion
	}

#pragma region Destroy Resource
	rdrInter->DestroyDefaultGraphicPipeline(defaultPipeline);

	delete model;
	delete texture;
	delete vertShader;
	delete fragShader;
	delete shaderProgram;
	delete modelSkybox;
	delete vertShaderSkybox;
	delete fragShaderSkybox;
	delete shaderProgramSkybox;
	delete skybox;
	delete vertShaderDeferredRendering;
	delete fragShaderDeferredRendering;
	delete shaderProgramDeferredRendering;
	delete vertShaderDeferredLighting;
	delete fragShaderDeferredLighting;
	delete shaderProgramDeferredLighting;
	Resource::ResourceManager::GetInstance().DestroyInstance();
	delete rdrInter;
#pragma endregion

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
	delete window;
	return 0;
}

