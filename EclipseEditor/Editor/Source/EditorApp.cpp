#include "EditorApp.hpp"
#include "Windowing/GLFWWindow.hpp"
#include "RHIOpenGL/OpenGLRenderInterface.hpp"

#include "Resource/ResourceManager.hpp"
#include "Resource/ModelData.hpp"

#include "GUI/Widget/ImGuiWidget.hpp"

#include "iostream"

EditorApp::EditorApp(const char* _windowName, int _width, int _height)
	: m_width(_width),
	m_height(_height)
{
	InitWindowing(_windowName);
	InitGUI();
	InitRHI();
	LoadScene();
}

EditorApp::~EditorApp()
{
}

bool EditorApp::ShouldClose()
{
	return m_window->WindowShouldClose();
}

void EditorApp::Update()
{
	m_window->UpdateInputs();

	if (m_window->GetKey(Windowing::KEY_CODE::KEY_ESCAPE, Windowing::INPUT_ACTION::INPUT_PRESS))
		m_window->SetWindowShouldClose(true);

	deltaTime = m_window->GetTime() - oldTime;
	oldTime = m_window->GetTime();


	m_sceneCamera.Update(m_window, deltaTime, { static_cast<float>(m_scenePosX), static_cast<float>(m_scenePosY)}, { static_cast<float>(m_sceneWidth), static_cast<float>(m_sceneHeight)});
	m_defaultPipeline->Rescale(m_sceneWidth, m_sceneHeight);
	m_renderInterface->Viewport(0, 0, m_sceneWidth, m_sceneHeight);


	m_scene.Update();

	m_window->PollEvents();
}

void EditorApp::Render()
{
	GUI::BeginNewFrame();
	m_dockingGUI.Start();
	Core::GameObject* newGOSelected = m_hierarchyGUI.Draw(&m_scene, m_crtGOSelected);
	if (newGOSelected)
		m_crtGOSelected = newGOSelected;
	m_inspectorGUI.Draw(m_crtGOSelected);
	m_sceneGUI.Draw(m_defaultPipeline->GetFinalTexture(), m_sceneWidth, m_sceneHeight, m_scenePosX, m_scenePosY);
	m_consoleGUI.Draw();
	m_contentBrowserGUI.Draw();
	GUI::EndFrame();

	DrawScene();

	GUI::RenderGUI();
	m_dockingGUI.End();
	m_window->SwapBuffers();
}

void EditorApp::Destroy()
{
	DestroyScene();
	DestroyGUI();

	m_renderInterface->DestroyDefaultGraphicPipeline(m_defaultPipeline);
	delete m_renderInterface;
	m_window->DestroyWindow();
	delete m_window;
}

void EditorApp::InitWindowing(const char* _windowName)
{
	m_window = new Windowing::GLFWWindow;
	m_window->CreateWindow(_windowName, m_width, m_height);
}

void EditorApp::InitRHI()
{
	m_renderInterface = new RHI::OpenGL::OpenGLRenderInterface;
	if (!m_renderInterface->InitGraphicsAPI())
	{
		m_window->DestroyWindow();
		std::cout << "Failed to init graphics API!" << std::endl;
		return;
	}
	m_renderInterface->EnableContextCapability(RHI::IFLAGS::DEPTH_TEST);
}

void EditorApp::InitGUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	ImGui::StyleColorsDark();

#ifdef ImGuiImplementGLFW
	ImGui_ImplGlfw_InitForOpenGL(m_window->CastGLFW()->GetWindow(), true);
#endif // ImGuiImplementGLFW

#ifdef ImGuiImplementOpenGL
	ImGui_ImplOpenGL3_Init("#version 330");
#endif // ImGuiImplementOpenGL
}

void EditorApp::LoadScene()
{
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("MeshIcon.img", "Assets/Icons/MeshIcon.jpg");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("FolderIcon.img", "Assets/Icons/FolderIcon.png");
	
	Resource::Mesh* model = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Mesh>("VikingRoom.obj", "Assets/Models/VikingRoom.obj");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Mesh>("Avion.obj", "Assets/Models/Avion.obj");
	Resource::Texture* texture = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("VikingRoom.img", "Assets/Textures/VikingRoom.png");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("PopCat.img", "Assets/Textures/PopCat.png");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("Avion.img", "Assets/Textures/Avion.jpg");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("Bunny.img", "Assets/Textures/Bunny.jpg");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("Earth.img", "Assets/Textures/Earth.jpg");

	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("DefaultDeferredRendering.vert", "Assets/Shaders/DeferredRendering/DefaultDeferredRendering.vert");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("DefaultDeferredRendering.frag", "Assets/Shaders/DeferredRendering/DefaultDeferredRendering.frag");
	Resource::ShaderProgram* shaderProgramDeferredRendering = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("DefaultDeferredRendering.shd", "DefaultDeferredRendering.vert", "DefaultDeferredRendering.frag");

	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("DeferredLighting.vert", "Assets/Shaders/DeferredRendering/DeferredLighting.vert");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("DeferredLighting.frag", "Assets/Shaders/DeferredRendering/DeferredLighting.frag");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("DeferredLighting.shd", "DeferredLighting.vert", "DeferredLighting.frag");

	Resource::ResourceManager::GetInstance().LoadAllResources();
	Resource::ResourceManager::GetInstance().GenerateAllResources(m_renderInterface);

	m_contentBrowserGUI.Init();
	m_defaultPipeline = m_renderInterface->InstantiateDefaultGraphicPipeline();
	m_defaultPipeline->Init(m_window->width, m_window->height);

	// CORE TESTS
	Core::GameObject* obj1_1 = m_scene.CreateGameObject();
	obj1_1->transform->localPosition = Math::Vec3(1.f, 1.f, 0.f);
	obj1_1->transform->localScale = Math::Vec3(0.5f, 0.5f, 0.5f);
	obj1_1->AddComponent(new Core::Model(model, texture, shaderProgramDeferredRendering));

	Core::GameObject* obj1 = m_scene.CreateGameObject();
	obj1->transform->localPosition = Math::Vec3(-1.f, 0.f, 0.f);
	obj1->transform->localScale = Math::Vec3(0.5f, 0.5f, 0.5f);
	obj1->AddComponent(new Core::Model(model, texture, shaderProgramDeferredRendering));
	
	// TODO Simplifier AddChild et SetParent (les combiner et retirer le transform de la root)
	obj1->transform->AddChild(obj1_1->transform);
	obj1_1->transform->SetParent(obj1->transform);
	m_scene.m_transformSystem.m_root->RemoveChild(obj1_1->transform);

	Core::GameObject* obj2 = m_scene.CreateGameObject();
	obj2->transform->localPosition = Math::Vec3(0.f, 0.f, 0.f);
	obj2->transform->localScale = Math::Vec3(0.5f, 0.5f, 0.5f);
	obj2->AddComponent(new Core::Model(model, texture, shaderProgramDeferredRendering));

	Core::GameObject* obj3 = m_scene.CreateGameObject();
	obj3->transform->localPosition = Math::Vec3(1.f, 0.f, 0.f);
	obj3->transform->localScale = Math::Vec3(0.5f, 0.5f, 0.5f);
	obj3->AddComponent(new Core::Model(model, texture, shaderProgramDeferredRendering));
}

void EditorApp::DrawScene()
{
	m_renderInterface->ClearBackgroundColor({ 0.f, 0.f, 0.f });
	m_renderInterface->ClearBuffer(RHI::IFLAGS::COLOR_BUFFER_BIT);
	m_renderInterface->ClearBuffer(RHI::IFLAGS::DEPTH_BUFFER_BIT);

	std::vector<Resource::ModelData> staticModels;
	Core::GameObject* obj;
	Core::Model* addModel;
	Resource::ModelData modelData;
	Core::Transform* root = m_scene.GetTransforms();
	for (int i = 0; i < root->GetChildren().size(); ++i)
	{
		obj = root->GetChildren()[i]->GetGameObject();
		addModel = obj->GetComponent<Core::Model>();
		modelData = addModel->GetModelData();
		staticModels.push_back(modelData);
	}

	m_defaultPipeline->Draw(m_sceneCamera.GetVP(), m_sceneCamera.GetViewPos(), staticModels);
}

void EditorApp::DestroyScene()
{
	m_contentBrowserGUI.Delete();
	Resource::ResourceManager::GetInstance().DestroyInstance();
}

void EditorApp::DestroyGUI()
{
#ifdef ImGuiImplementOpenGL
	ImGui_ImplOpenGL3_Shutdown();
#endif // ImGuiImplementOpenGL

#ifdef ImGuiImplementGLFW
	ImGui_ImplGlfw_Shutdown();
#endif // ImGuiImplementGLFW

	ImGui::DestroyContext();
}