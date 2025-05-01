#include "EditorApp.hpp"

#include "Logger.hpp"

#include "Windowing/GLFWWindow.hpp"
#include "RHIOpenGL/OpenGLRenderInterface.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/ModelData.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Core/Physics/BoxCollider.hpp"
#include "Lighting/DirectionalLight.hpp"
#include "Lighting/PointLight.hpp"
#include "Lighting/SpotLight.hpp"

EditorApp::EditorApp(const char* _windowName, int _width, int _height)
	: m_width(_width),
	m_height(_height)
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "EditorApp initialization!");
	InitWindowing(_windowName);
	InitGUI();
	InitRHI();
	LoadScene();
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::WARNING, "EditorApp is created!");

	m_scene.GetSystemManager()->GetAudioSystem()->PlayStartUp();
}

EditorApp::~EditorApp()
{
	Logging::Logger::DestroyInstance();
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


	m_sceneCamera.Update(m_window, deltaTime, { static_cast<float>(m_scenePosX), static_cast<float>(m_scenePosY) }, { static_cast<float>(m_sceneWidth), static_cast<float>(m_sceneHeight) });
	m_defaultPipeline->Rescale(m_sceneWidth, m_sceneHeight);
	m_renderInterface->Viewport(0, 0, m_sceneWidth, m_sceneHeight);

	m_sceneGUI.UpdateGizmoMode(m_window);
	m_scene.Update(deltaTime);

	m_window->PollEvents();
}

void EditorApp::Render()
{
	GUI::BeginNewFrame();
	m_sceneGUI.StartGizmo();
	m_dockingGUI.Start();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File", true))
		{
			if (ImGui::MenuItem("Save"))
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "Save");
			if (ImGui::MenuItem("Load"))
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "Load");
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows", true))
		{
			ImGui::MenuItem("Hierarchy", "", &bIsHierarchieWindowEnabled);
			ImGui::MenuItem("Inspector", "", &bIsInspectorWindowEnabled);
			ImGui::MenuItem("Scene", "", &bIsSceneWindowEnabled);
			ImGui::MenuItem("Game", "", &bIsGameWindowEnabled);
			ImGui::MenuItem("Content Browser", "", &bIsContentBrowserWindowEnabled);
			ImGui::MenuItem("Console", "", &bIsConsoleWindowEnabled);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (m_crtGOSelected)
	{
		if (m_crtGOSelected->IsDestroyed())
			m_crtGOSelected = nullptr;
	}

	if (bIsHierarchieWindowEnabled)
	{
		Core::GameObject* newGOSelected = m_hierarchyGUI.Draw(&m_scene, m_crtGOSelected);
		if (newGOSelected)
			m_crtGOSelected = newGOSelected;
	}

	if (bIsInspectorWindowEnabled)
		m_inspectorGUI.Draw(m_crtGOSelected);

	if (bIsSceneWindowEnabled)
		m_sceneGUI.Draw(m_crtGOSelected, &m_sceneCamera, m_defaultPipeline->GetFinalTexture(), m_sceneWidth, m_sceneHeight, m_scenePosX, m_scenePosY);

	if (bIsGameWindowEnabled)
		m_gameGUI.Draw();

	if (bIsConsoleWindowEnabled)
		m_consoleGUI.Draw();

	if (bIsContentBrowserWindowEnabled)
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

	io.IniFilename = "Assets/editor.ini";
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/SourceSans3-Medium.ttf", 24);

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
	Resource::Mesh* cubeModel = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Mesh>("Cube.obj", "Assets/Models/Cube.obj");
	Resource::Texture* texture = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("VikingRoom.img", "Assets/Textures/VikingRoom.png");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("PopCat.img", "Assets/Textures/PopCat.png");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("Avion.img", "Assets/Textures/Avion.jpg");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("Bunny.img", "Assets/Textures/Bunny.jpg");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("Earth.img", "Assets/Textures/Earth.jpg");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("WhiteTexture.img", "Assets/Textures/WhiteTexture.png");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("TranslateGizmoIcon.img", "Assets/Icons/TranslateGizmoIcon.png");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("RotateGizmoIcon.img", "Assets/Icons/RotateGizmoIcon.png");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Texture>("ScaleGizmoIcon.img", "Assets/Icons/ScaleGizmoIcon.png");


	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("SkyboxShader.vert", "Assets/Shaders/Skybox/SkyboxShader.vert");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("SkyboxShader.frag", "Assets/Shaders/Skybox/SkyboxShader.frag");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("SkyboxShader.shd", "SkyboxShader.vert", "SkyboxShader.frag");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::Skybox>("Skybox.skb", "Assets/Skybox/Default", "Cube.obj");

	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("DefaultDeferredRendering.vert", "Assets/Shaders/DeferredRendering/DefaultDeferredRendering.vert");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("DefaultDeferredRendering.frag", "Assets/Shaders/DeferredRendering/DefaultDeferredRendering.frag");
	Resource::ShaderProgram* shaderProgramDeferredRendering = Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("DefaultDeferredRendering.shd", "DefaultDeferredRendering.vert", "DefaultDeferredRendering.frag");

	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::VertShader>("DeferredLighting.vert", "Assets/Shaders/DeferredRendering/DeferredLighting.vert");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::FragShader>("DeferredLighting.frag", "Assets/Shaders/DeferredRendering/DeferredLighting.frag");
	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::ShaderProgram>("DeferredLighting.shd", "DeferredLighting.vert", "DeferredLighting.frag");

	Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::AudioClip>("TestAudio.mp3", "Assets/Audio/startup.mp3");

	Resource::ResourceManager::GetInstance().LoadAllResources();
	Resource::ResourceManager::GetInstance().GenerateAllResources(m_renderInterface);

	m_contentBrowserGUI.Init();
	m_defaultPipeline = m_renderInterface->InstantiateDefaultGraphicPipeline();
	m_defaultPipeline->Init(m_window->width, m_window->height);


	// CORE TESTS

	Core::GameObject* floor = m_scene.CreateGameObject();
	floor->name = "Floor";
	floor->transform->SetLocalPosition(Math::Vec3(0.f, -1.f, 0.f));
	floor->transform->SetLocalScale(Math::Vec3(100.f, 0.1f, 100.f));
	Core::Model* floorModel = floor->AddComponent<Core::Model>();
	floorModel->SetData(cubeModel, texture, shaderProgramDeferredRendering);
	Core::BoxCollider* floorCollider = floor->AddComponent<Core::BoxCollider>();
	floorCollider->SetPosition(0.f, -1.f, 0.f);
	floorCollider->Scale(100.f, 0.1f, 100.f);

	Core::GameObject* vikingRoomObject = m_scene.CreateGameObject();
	vikingRoomObject->name = "VikingRoom";
	vikingRoomObject->transform->SetLocalPosition({ 0.f, 1.f, 0.f });
	vikingRoomObject->transform->SetLocalScale({ 1.f, 1.f, 1.f });
	Core::Model* vikingRoomModelObject = vikingRoomObject->AddComponent<Core::Model>();
	vikingRoomModelObject->SetData(model, texture, shaderProgramDeferredRendering);
	Core::MeshCollider* vikingRoomMeshCollider = vikingRoomObject->AddComponent<Core::MeshCollider>();
	vikingRoomMeshCollider->SetPosition(-2.f, 50.f, 0.f);
	vikingRoomMeshCollider->SetMesh(model);

	Core::GameObject* obj1 = m_scene.CreateGameObject();
	obj1->name = "Capsule1";
	obj1->transform->SetLocalPosition({ -1.f, 0.f, 0.f });
	obj1->transform->SetLocalScale({ 1.f, 2.f, 1.f });
	Core::Model* model2 = obj1->AddComponent<Core::Model>();
	model2->SetData(cubeModel, texture, shaderProgramDeferredRendering);
	Core::CapsuleCollider* cc = obj1->AddComponent<Core::CapsuleCollider>();
	cc->SetPosition(0.1f, 50.f, 0.f);
	cc->SetDynamic(true);

	Core::GameObject* capsule2 = m_scene.CreateGameObject();
	capsule2->name = "Capsule2";
	capsule2->transform->SetLocalPosition({ -1.f, 0.f, 0.f });
	capsule2->transform->SetLocalScale({ 1.f, 2.f, 1.f });
	Core::Model* capsuleModel2 = capsule2->AddComponent<Core::Model>();
	capsuleModel2->SetData(cubeModel, texture, shaderProgramDeferredRendering);
	Core::CapsuleCollider* cc2 = capsule2->AddComponent<Core::CapsuleCollider>();
	cc2->SetPosition(3.5f, 75.f, 0.1f);
	cc2->SetRotation(0.f, 0.f, 0.2f);
	cc2->SetDynamic(true);

	Core::GameObject* obj2 = m_scene.CreateGameObject();
	obj2->name = "BoxCollider Static";
	obj2->transform->SetLocalPosition({ 0.f, 0.f, 0.f });
	obj2->transform->SetLocalScale({ 0.5f, 0.5f, 0.5f });
	Core::Model* model3 = obj2->AddComponent<Core::Model>();
	model3->SetData(cubeModel, texture, shaderProgramDeferredRendering);
	obj2->AddComponent<Core::BoxCollider>();

	Core::GameObject* obj3 = m_scene.CreateGameObject();
	obj3->name = "BoxCollider Dynamic";
	obj3->transform->SetLocalPosition({ 1.f, 0.f, 0.f });
	obj3->transform->SetLocalScale({ 1.f, 1.f, 1.f });
	Core::Model* model4 = obj3->AddComponent<Core::Model>();
	model4->SetData(cubeModel, texture, shaderProgramDeferredRendering);
	Core::BoxCollider* bc = obj3->AddComponent<Core::BoxCollider>();
	bc->SetPosition(1.f, 0.f, 0.f);
	bc->SetDynamic(true);
	bc->AddForce(0.f, 0.f, 20.f);
	bc->AddImpulse(0.f, 5.f, 0.f);

	Core::GameObject* parent = m_scene.CreateGameObject();
	parent->name = "Parent";
	parent->transform->SetLocalPosition({ -1.f, 1.5f, 0.f });
	parent->transform->SetLocalScale({ 1.f, 1.f, 1.f });
	Core::Model* model5 = parent->AddComponent<Core::Model>();
	model5->SetData(model, texture, shaderProgramDeferredRendering);

	Core::GameObject* child = m_scene.CreateGameObject();
	child->name = "Child";
	child->transform->SetLocalPosition({ 1.f, 1.f, 0.f });
	child->transform->SetLocalScale({ 0.5f, 0.5f, 0.5f });
	Core::Model* model6 = child->AddComponent<Core::Model>();
	model6->SetData(model, texture, shaderProgramDeferredRendering);
	parent->transform->AddChild(child->transform);

	// LIGHTS
	Core::GameObject* dirLight = m_scene.CreateGameObject();
	dirLight->transform->SetLocalPosition(Math::Vec3(0.f, 0.f, 0.f));
	dirLight->transform->SetLocalScale(Math::Vec3(1.f, 1.f, 1.f));
	dirLight->transform->SetLocalEulerAngles(Math::Vec3(-180.f, 0.f, 0.f));
	dirLight->name = "DirectionalLight";
	Core::DirectionalLight* dirLightComp = dirLight->AddComponent<Core::DirectionalLight>();
	dirLightComp->SetColor({ 1.f, 0.9f, 0.76f, 1.f });

	Core::GameObject* pointLight = m_scene.CreateGameObject();
	pointLight->transform->SetLocalPosition(Math::Vec3(0.f, 0.f, 0.f));
	pointLight->transform->SetLocalScale(Math::Vec3(1.f, 1.f, 1.f));
	pointLight->name = "PointLight";
	Core::PointLight* pointLightComp = pointLight->AddComponent<Core::PointLight>();
	pointLightComp->SetColor({ 0.f, 0.f, 1.f, 1.f });

	Core::GameObject* spotLight = m_scene.CreateGameObject();
	spotLight->transform->SetLocalPosition(Math::Vec3(0.f, 0.f, 0.f));
	spotLight->transform->SetLocalScale(Math::Vec3(1.f, 1.f, 1.f));
	spotLight->name = "SpotLight";
	Core::SpotLight* spotLightComp = spotLight->AddComponent<Core::SpotLight>();
	spotLightComp->SetColor({ 1.f, 0.f, 0.f, 1.f });

	Core::GameObject* soundTest = m_scene.CreateGameObject();
	soundTest->transform->SetLocalPosition(Math::Vec3(0.f, 0.f, 0.f));
	soundTest->name = "Sound Test";
	soundTest->AddComponent<Core::AudioEmitter>();
	
}

void EditorApp::DrawScene()
{
	m_scene.GetSystemManager()->Render(m_renderInterface, m_defaultPipeline, m_sceneCamera.GetVP(), m_sceneCamera.GetViewPos());
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