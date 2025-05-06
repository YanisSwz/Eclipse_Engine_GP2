#include "EditorApp.hpp"


#include "Logger.hpp"
#include "Windowing/GLFWWindow.hpp"
#include "RHIOpenGL/OpenGLRenderInterface.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/GeoShader.hpp"
#include "Resource/ModelData.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Core/Physics/BoxCollider.hpp"
#include "Lighting/DirectionalLight.hpp"
#include "Lighting/PointLight.hpp"
#include "Lighting/SpotLight.hpp"

#include "Serializer.hpp"

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
	m_window->UpdateWindowSize();
	m_window->UpdateInputs();

	if (m_window->GetKey(Windowing::KEY_CODE::KEY_ESCAPE, Windowing::INPUT_ACTION::INPUT_PRESS))
		m_window->SetWindowShouldClose(true);

	PickObjectID();

	deltaTime = m_window->GetTime() - oldTime;
	oldTime = m_window->GetTime();

	Math::Vec2 windowPos = m_window->GetWindowPos();

	m_sceneCamera.Update(m_window, deltaTime, { static_cast<float>(m_sceneWindowPosX) - windowPos.x, static_cast<float>(m_sceneWindowPosY) - windowPos.y }, { static_cast<float>(m_sceneWindowWidth), static_cast<float>(m_sceneWindowHeight) });

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

		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.f - 55.f);
		GAME_STATE gameState = m_scene.GetState();
		if (gameState == GAME_STATE::STOP)
		{
			// Play Button
			if (ImGui::Button("Play", { 50.f, 30.f }))
			{
				m_scene.SetState(GAME_STATE::PLAY);
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Play!");
				ImGui::SetWindowFocus("Game");
			}
		}
		else
		{
			// Stop Button
			if (ImGui::Button("Stop", { 50.f, 30.f }))
			{
				m_scene.SetState(GAME_STATE::STOP);
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Stop!");
				ImGui::SetWindowFocus("Scene");
			}
		}

		if (gameState == GAME_STATE::PAUSE)
		{
			// Resume Button
			if (ImGui::Button("Resume", { 50.f, 30.f }))
			{
				m_scene.SetState(GAME_STATE::PLAY);
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Resume!");
			}
		}
		else
		{
			// Pause Button
			ImGui::BeginDisabled(gameState == GAME_STATE::STOP);
			if (ImGui::Button("Pause", { 50.f, 30.f }))
			{
				m_scene.SetState(GAME_STATE::PAUSE);
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Pause!");
			}
			ImGui::EndDisabled();
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
		m_sceneGUI.Draw(m_crtGOSelected, &m_sceneCamera, m_editorPipeline->GetFinalTexture(), m_sceneWindowWidth, m_sceneWindowHeight, m_sceneWindowPosX, m_sceneWindowPosY);

	if (bIsGameWindowEnabled)
		m_gameGUI.Draw(m_scene.GetSystemManager()->GetCameraSystem()->GetCurrentCamera(), m_gamePipeline->GetFinalTexture(), m_gameWindowWidth, m_gameWindowHeight);

	if (bIsConsoleWindowEnabled)
		m_consoleGUI.Draw();

	if (bIsContentBrowserWindowEnabled)
		m_contentBrowserGUI.Draw();

	GUI::EndFrame();

	DrawScene();

	GUI::RenderGUI();
	m_dockingGUI.End(m_window);
	m_window->SwapBuffers();
}

void EditorApp::Destroy()
{
	DestroyScene();
	DestroyGUI();

	m_renderInterface->DestroyDefaultGraphicPipeline(m_editorPipeline);
	m_renderInterface->DestroyDefaultGraphicPipeline(m_gamePipeline);
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
	//Resource::ResourceManager::GetInstance().AddResourceToLoad<Resource::GeoShader>("GeometryShader.geom", "Assets/Shaders/GeometryShader.geom");

	// Load All Resources
	Resource::ResourceManager::GetInstance().LoadAllResourcesInAssetsFolder();
	Resource::ResourceManager::GetInstance().LoadAllResources();
	Resource::ResourceManager::GetInstance().GenerateAllResources(m_renderInterface);


	Resource::Mesh* cubeMesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("Cube.obj");
	Resource::Mesh* vikingRoomMesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("VikingRoom.obj");
	Resource::Texture* texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("VikingRoom.img");
	Resource::ShaderProgram* shaderProgramDeferredRendering = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>("DefaultDeferredRendering.shd");
	
	m_contentBrowserGUI.Init();
	m_editorPipeline = m_renderInterface->InstantiateDefaultGraphicPipeline();
	m_editorPipeline->Init(m_window->width, m_window->height);
	m_gamePipeline = m_renderInterface->InstantiateDefaultGraphicPipeline();
	m_gamePipeline->Init(m_window->width, m_window->height);

	// CORE TESTS
	Core::GameObject* floor = m_scene.CreateGameObject();
	floor->name = "Floor";
	floor->transform->SetLocalPosition(0.f, -1.f, 0.f);
	floor->transform->SetLocalScale(100.f, 0.1f, 100.f);
	Core::Model* floorModel = floor->AddComponent<Core::Model>();
	floorModel->SetData(cubeMesh, texture, shaderProgramDeferredRendering);
	Core::BoxCollider* floorCollider = floor->AddComponent<Core::BoxCollider>();
	floorCollider->SetPosition(0.f, -1.f, 0.f);
	floorCollider->Scale(100.f, 0.1f, 100.f);

	Core::GameObject* vikingRoomObject = m_scene.CreateGameObject();
	vikingRoomObject->name = "VikingRoom";
	vikingRoomObject->transform->SetLocalPosition(0.f, 1.f, 0.f);
	vikingRoomObject->transform->SetLocalScale(1.f, 1.f, 1.f);
	Core::Model* vikingRoomModelObject = vikingRoomObject->AddComponent<Core::Model>();
	vikingRoomModelObject->SetData(vikingRoomMesh, texture, shaderProgramDeferredRendering);
	Core::MeshCollider* vikingRoomMeshCollider = vikingRoomObject->AddComponent<Core::MeshCollider>();
	vikingRoomMeshCollider->SetPosition(-2.f, 5.f, 0.f);
	vikingRoomMeshCollider->SetMesh(vikingRoomMesh);

	Core::GameObject* obj1 = m_scene.CreateGameObject();
	obj1->name = "Capsule1";
	obj1->transform->SetLocalPosition(-1.f, 0.f, 0.f);
	obj1->transform->SetLocalScale(1.f, 2.f, 1.f);
	Core::Model* model2 = obj1->AddComponent<Core::Model>();
	model2->SetData(cubeMesh, texture, shaderProgramDeferredRendering);
	Core::CapsuleCollider* cc = obj1->AddComponent<Core::CapsuleCollider>();
	cc->SetPosition(0.1f, 50.f, 0.f);
	cc->SetDynamic(true);

	Core::GameObject* capsule2 = m_scene.CreateGameObject();
	capsule2->name = "Capsule2";
	capsule2->transform->SetLocalPosition(-1.f, 0.f, 0.f);
	capsule2->transform->SetLocalScale(1.f, 2.f, 1.f);
	Core::Model* capsuleModel2 = capsule2->AddComponent<Core::Model>();
	capsuleModel2->SetData(cubeMesh, texture, shaderProgramDeferredRendering);
	Core::CapsuleCollider* cc2 = capsule2->AddComponent<Core::CapsuleCollider>();
	cc2->SetPosition(3.5f, 75.f, 0.1f);
	cc2->SetRotation(0.f, 0.f, 0.2f);
	cc2->SetDynamic(true);

	Core::GameObject* obj2 = m_scene.CreateGameObject();
	obj2->name = "BoxCollider Static";
	obj2->transform->SetLocalPosition(0.f, 0.f, 0.f);
	obj2->transform->SetLocalScale(0.5f, 0.5f, 0.5f);
	Core::Model* model3 = obj2->AddComponent<Core::Model>();
	model3->SetData(cubeMesh, texture, shaderProgramDeferredRendering);
	obj2->AddComponent<Core::BoxCollider>();

	Core::GameObject* obj3 = m_scene.CreateGameObject();
	obj3->name = "BoxCollider Dynamic";
	obj3->transform->SetLocalPosition(1.f, 0.f, 0.f);
	obj3->transform->SetLocalScale(1.f, 1.f, 1.f);
	Core::Model* model4 = obj3->AddComponent<Core::Model>();
	model4->SetData(cubeMesh, texture, shaderProgramDeferredRendering);
	Core::BoxCollider* bc = obj3->AddComponent<Core::BoxCollider>();
	bc->SetPosition(1.f, 0.f, 0.f);
	bc->SetDynamic(true);
	bc->AddForce(0.f, 0.f, 20.f);
	bc->AddImpulse(0.f, 5.f, 0.f);

	Core::GameObject* parent = m_scene.CreateGameObject();
	parent->name = "Parent";
	parent->transform->SetLocalPosition(-1.f, 1.5f, 0.f);
	parent->transform->SetLocalScale(1.f, 1.f, 1.f);
	Core::Model* model5 = parent->AddComponent<Core::Model>();
	model5->SetData(vikingRoomMesh, texture, shaderProgramDeferredRendering);

	Core::GameObject* child = m_scene.CreateGameObject();
	child->name = "Child";
	child->transform->SetLocalPosition(1.f, 1.f, 0.f);
	child->transform->SetLocalScale(0.5f, 0.5f, 0.5f);
	Core::Model* model6 = child->AddComponent<Core::Model>();
	model6->SetData(vikingRoomMesh, texture, shaderProgramDeferredRendering);
	parent->transform->AddChild(child->transform);

	// LIGHTS
	Core::GameObject* dirLight = m_scene.CreateGameObject();
	dirLight->transform->SetLocalPosition(0.f, 0.f, 0.f);
	dirLight->transform->SetLocalScale(1.f, 1.f, 1.f);
	dirLight->transform->SetLocalEulerAngles(-180.f, 0.f, 0.f);
	dirLight->name = "DirectionalLight";
	Core::DirectionalLight* dirLightComp = dirLight->AddComponent<Core::DirectionalLight>();
	dirLightComp->SetColor(1.f, 0.9f, 0.76f, 1.f);

	Core::GameObject* pointLight = m_scene.CreateGameObject();
	pointLight->transform->SetLocalPosition(0.f, 0.f, 0.f);
	pointLight->transform->SetLocalScale(1.f, 1.f, 1.f);
	pointLight->name = "PointLight";
	Core::PointLight* pointLightComp = pointLight->AddComponent<Core::PointLight>();
	pointLightComp->SetColor(0.f, 0.f, 1.f, 1.f);

	Core::GameObject* spotLight = m_scene.CreateGameObject();
	spotLight->transform->SetLocalPosition(0.f, 0.f, 0.f);
	spotLight->transform->SetLocalScale(1.f, 1.f, 1.f);
	spotLight->transform->SetLocalEulerAngles(90.f, 0.f, 0.f);
	spotLight->name = "SpotLight";
	Core::SpotLight* spotLightComp = spotLight->AddComponent<Core::SpotLight>();
	spotLightComp->SetColor({ 1.f, 0.f, 0.f, 1.f });

	Core::GameObject* soundTest = m_scene.CreateGameObject();
	soundTest->transform->SetLocalPosition(Math::Vec3(0.f, 0.f, 0.f));
	soundTest->name = "Sound Test";
	soundTest->AddComponent<Core::AudioSource>();
	Core::Serializer serializer;
	serializer.SerializeSceneToFile(&m_scene, "Assets/Scenes/Scene.json");
}

void EditorApp::DrawScene()
{
	m_editorPipeline->Rescale(m_sceneWindowWidth, m_sceneWindowHeight);
	m_renderInterface->Viewport(0, 0, m_sceneWindowWidth, m_sceneWindowHeight);
	m_scene.GetSystemManager()->Render(m_renderInterface, m_editorPipeline, m_sceneCamera.GetVP(), m_sceneCamera.GetViewPos());
	
	m_gamePipeline->Rescale(m_gameWindowWidth, m_gameWindowHeight);
	m_renderInterface->Viewport(0, 0, m_gameWindowWidth, m_gameWindowHeight);
	Core::Camera* gameCamera = m_scene.GetSystemManager()->GetCameraSystem()->GetCurrentCamera();
	if (gameCamera)
		m_scene.GetSystemManager()->Render(m_renderInterface, m_gamePipeline, gameCamera->GetViewProjectionMatrix(m_gameWindowWidth, m_gameWindowHeight), gameCamera->GetViewPos());
}

void EditorApp::PickObjectID()
{
	if (m_window->GetMouseButton(Windowing::MOUSE_CODE::MIDDLE_BUTTON, Windowing::INPUT_ACTION::INPUT_PRESS))
	{
		Math::Vec2 mousePos = m_window->GetCursorPos();
		int mousePosX = static_cast<int>(mousePos.x) - m_sceneWindowPosX;
		int mousePosY = m_sceneWindowHeight - static_cast<int>(mousePos.y) - m_sceneWindowPosY - 30; // -30 for the size of the ImGui window titlebar
		int pickID = m_editorPipeline->PickObjectID(mousePosX, mousePosY);
		
		m_crtGOSelected = m_scene.GetObjectByID(pickID);
	}
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