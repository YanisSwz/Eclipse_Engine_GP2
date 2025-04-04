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
#include "Scene.hpp"
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
	

	Resource::ResourceManager::GetInstance().LoadAllResources();
	Resource::ResourceManager::GetInstance().GenerateAllResources(rdrInter);
	Resource::ResourceManager::GetInstance().GenerateAllResources(rdrInter);


#pragma region Generate FrameBuffer
	RHI::IFrameBuffer* FB = rdrInter->InstantiateFrameBuffer();
	FB->Init(window->width, window->height);
#pragma endregion

	Core::SceneCamera sceneCamera{ 60.f, 0.1f, 100.f };

	float deltaTime = 0.f;
	float oldTime = 0.f;
	float crtAngle = 0.f;
	float speed = 1.f;
	Math::Mat4 TRS;
	
	// CORE TESTS
	Core::Scene scene{};
	scene.CreateGameObject();

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
		ImGui::Begin("Scene", 0);
		ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
		ImVec2 cursorPos = ImGui::GetCursorScreenPos();

		FB->Rescale(static_cast<int>(contentRegionAvailable.x), static_cast<int>(contentRegionAvailable.y));
		sceneCamera.Update(window, deltaTime, { cursorPos.x, cursorPos.y }, { contentRegionAvailable.x, contentRegionAvailable.y });
		rdrInter->Viewport(0, 0, static_cast<int>(contentRegionAvailable.x), static_cast<int>(contentRegionAvailable.y));

		ImGui::GetWindowDrawList()->AddImage(
			(intptr_t)(FB->GetTextureID()),
			ImVec2(cursorPos.x, cursorPos.y),
			ImVec2(cursorPos.x + contentRegionAvailable.x, cursorPos.y + contentRegionAvailable.y),
			ImVec2(0, 1),
			ImVec2(1, 0));

		ImGui::End();
		ImGui::Render();

		rdrInter->ClearBackgroundColor({ 1.f, 0.f, 0.f });
		rdrInter->ClearBuffer(RHI::IFLAGS::COLOR_BUFFER_BIT);
		rdrInter->ClearBuffer(RHI::IFLAGS::DEPTH_BUFFER_BIT);

#pragma region Draw
		FB->Bind();
		//Draw Background of OpenGL Window
		rdrInter->ClearBackgroundColor({ 0.07f, 0.13f, 0.17f });
		rdrInter->ClearBuffer(RHI::IFLAGS::COLOR_BUFFER_BIT);
		rdrInter->ClearBuffer(RHI::IFLAGS::DEPTH_BUFFER_BIT);

		sceneCamera.SetShaderData(shaderProgram, FB->width, FB->height);
		sceneCamera.SetShaderData(shaderProgramSkybox, FB->width, FB->height);

		// Update TRS Rotation
		TRS.SetTRS(Math::Vec3{ 0.f, 0.f, 0.f }, Math::Vec3{ crtAngle, Math::Tools::PI / 2.f + crtAngle, 0.f }, Math::Vec3{1.f, 1.f, 1.f});

		// Draw Model with the texture
		shaderProgram->Bind();
		shaderProgram->SetMat4("TRS", TRS);
		texture->Bind();
		model->Draw();
		texture->Unbind();
		shaderProgram->Unbind();

		// Draw Skybox
		skybox->Draw();
		FB->Unbind();
#pragma endregion

#ifdef ImGuiImplementOpenGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif // ImGuiImplementOpenGL

		window->SwapBuffers();
		window->PollEvents();
	}

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

#pragma region Destroy RHI Objects
	// Delete FrameBuffer
	FB->Delete();
	rdrInter->DestroyFrameBuffer(FB);
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

	delete rdrInter;
	delete window;
	return 0;
}

