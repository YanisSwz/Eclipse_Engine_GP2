#include "RHIInterfaces/IRenderInterface.hpp"
#include "RHIOpenGL/OpenGLRenderInterface.hpp"
#include "GLFWWindow.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

int main()
{
	std::vector<RHI::Vertex> vertexBuffer
	{
		{{ 0.5f, 0.5f, 0.0f },		{ 1.0f, 1.0f },		{ 0.f, 0.f, 1.f }},  // top right
		{{ 0.5f, -0.5f, 0.0f },		{ 1.0f, 0.0f },		{ 0.f, 0.f, 1.f }},  // bottom right
		{{ -0.5f, -0.5f, 0.0f },	{ 0.0f, 0.0 },		{ 0.f, 0.f, 1.f }},  // bottom left
		{{ -0.5f, 0.5f, 0.0f },		{ 0.0f, 1.0f },		{ 0.f, 0.f, 1.f }}   // top left 
	};

	std::vector<uint32_t> indexBuffer{ 0, 1, 2, 2, 3, 0 };

	IWindow* window = new GLFWWindow;
	window->CreateWindow("Eclipse Engine", 1080, 720);
	//window->SetCursorMode(CURSOR_MODE::CURSOR_DISABLED);

	RHI::IRenderInterface* rdrInter = new RHI::OpenGL::OpenGLRenderInterface;

	if (!rdrInter->InitGraphicsAPI())
	{
		window->DestroyWindow();
		return -1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window->CastGLFW()->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

#pragma region Generate Shader
	RHI::IVertexShader* vert = rdrInter->InstantiateVertexShader();
	RHI::IFragmentShader* frag = rdrInter->InstantiateFragmentShader();
	RHI::IShaderProgram* shader = rdrInter->InstantiateShaderProgram();

	vert->Init("Assets/Shaders/Default/Default.vert");
	frag->Init("Assets/Shaders/Default/Default.frag");
	shader->CreateProgram();
	shader->SetVertShader(*vert);
	shader->SetFragShader(*frag);
	shader->Link();

	rdrInter->DestroyVertexShader(vert);
	rdrInter->DestroyFragmentShader(frag);
#pragma endregion

#pragma region Generate Model
	RHI::IVertexArray* objectVertexArray = rdrInter->InstantiateVertexArray();
	RHI::IVertexBuffer* objectVertexBuffer = rdrInter->InstantiateVertexBuffer();
	RHI::IIndexBuffer* objectIndexBuffer = rdrInter->InstantiateIndexBuffer();

	objectVertexArray->Init();
	objectVertexArray->Bind();
	objectVertexBuffer->Init(&vertexBuffer[0], vertexBuffer.size() * sizeof(RHI::Vertex));
	objectIndexBuffer->Init(&indexBuffer[0], indexBuffer.size() * sizeof(uint32_t));

	// Vertex position,		 /	    Texture position,		/		Normal
	objectVertexArray->LinkVertexBuffer(*objectVertexBuffer, 0, 3, RHI::IFLAGS::TYPE_FLOAT, sizeof(RHI::Vertex), (void*)offsetof(RHI::Vertex, pos));
	objectVertexArray->LinkVertexBuffer(*objectVertexBuffer, 1, 2, RHI::IFLAGS::TYPE_FLOAT, sizeof(RHI::Vertex), (void*)offsetof(RHI::Vertex, textUV));
	objectVertexArray->LinkVertexBuffer(*objectVertexBuffer, 2, 3, RHI::IFLAGS::TYPE_FLOAT, sizeof(RHI::Vertex), (void*)offsetof(RHI::Vertex, normal));

	objectVertexArray->Unbind();
	objectVertexBuffer->Unbind();
	objectIndexBuffer->Unbind();
#pragma endregion

#pragma region Generate Texture
	RHI::ITexture2D* texture = rdrInter->InstantiateTexture2D();
	texture->Init("Assets/Textures/Avion.jpg");
#pragma endregion

#pragma region Generate FrameBuffer
	RHI::IFrameBuffer* FB = rdrInter->InstantiateFrameBuffer();
	FB->Init(window->width, window->height);
#pragma endregion

	float deltaTime = 0.f;
	float oldTime = 0.f;
	float crtAngle = 0.f;
	float speed = 1.f;
	Math::Mat4 TRS;

	while (!window->WindowShouldClose())
	{
		window->UpdateInputs();
		if (window->GetKey(KEY_ESCAPE, INPUT_PRESS))
		{
			window->SetWindowShouldClose(true);
		}

		// Update Delta Time and Model rotation
		deltaTime = window->GetTime() - oldTime;
		oldTime = window->GetTime();
		crtAngle += (deltaTime * speed);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// SCENE WINDOW
		ImGui::Begin("Scene", 0);
		ImVec2 sceneSize = ImGui::GetContentRegionAvail();
		FB->Rescale(static_cast<int>(sceneSize.x), static_cast<int>(sceneSize.y));
		//glViewport(0, 0, static_cast<GLsizei>(sceneSize.x), static_cast<GLsizei>(sceneSize.y));
		ImVec2 windowPos = ImGui::GetCursorScreenPos();

		ImGui::GetWindowDrawList()->AddImage(
			(intptr_t)(FB->GetTextureID()),
			ImVec2(windowPos.x, windowPos.y),
			ImVec2(windowPos.x + sceneSize.x, windowPos.y + sceneSize.y),
			ImVec2(0, 1),
			ImVec2(1, 0));

		ImGui::End();
		ImGui::Render();

		rdrInter->ClearBackgroundColor({ 0.f, 0.f, 0.f });
		rdrInter->ClearBuffer(RHI::IFLAGS::COLOR_BUFFER_BIT);
		rdrInter->ClearBuffer(RHI::IFLAGS::DEPTH_BUFFER_BIT);

		FB->Bind();
#pragma region Draw
		//Draw Background of OpenGL Window
		rdrInter->ClearBackgroundColor({ 0.07f, 0.13f, 0.17f });
		rdrInter->ClearBuffer(RHI::IFLAGS::COLOR_BUFFER_BIT);
		rdrInter->ClearBuffer(RHI::IFLAGS::DEPTH_BUFFER_BIT);

		// Update TRS Rotation
		TRS.RotateY(crtAngle);

		// Draw Model with the texture
		shader->Bind();
		shader->SetMat4("TRS", TRS);
		texture->Bind();
		objectIndexBuffer->Draw(objectVertexArray);
		texture->Unbind();
		shader->Unbind();
#pragma endregion
		FB->Unbind();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window->SwapBuffers();
		window->PollEvents();
	}

#pragma region Destroy RHI Objects
	// Delete Shader
	shader->Delete();
	rdrInter->DestroyShaderProgram(shader);

	// Delete Model
	vertexBuffer.clear();
	indexBuffer.clear();
	objectVertexArray->Delete();
	objectVertexBuffer->Delete();
	objectIndexBuffer->Delete();
	rdrInter->DestroyVertexArray(objectVertexArray);
	rdrInter->DestroyVertexBuffer(objectVertexBuffer);
	rdrInter->DestroyIndexBuffer(objectIndexBuffer);

	// Delete Texture
	texture->Delete();
	rdrInter->DestroyTexture2D(texture);

	// Delete FrameBuffer
	FB->Delete();
	rdrInter->DestroyFrameBuffer(FB);
#pragma endregion

#pragma region Destroy ImGUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#pragma endregion

	window->DestroyWindow();
	return 0;
}

