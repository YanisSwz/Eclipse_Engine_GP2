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
			{
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "Save");
				Core::Serializer serializer;
				serializer.SerializeSceneToFile(&m_scene, "Assets/Scenes/Scene.json");
			}
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
	// Load All Resources
	Resource::ResourceManager::GetInstance().LoadAllResourcesInAssetsFolder();
	Resource::ResourceManager::GetInstance().LoadAllResources();
	Resource::ResourceManager::GetInstance().GenerateAllResources(m_renderInterface);

	m_contentBrowserGUI.Init();
	m_editorPipeline = m_renderInterface->InstantiateDefaultGraphicPipeline();
	m_editorPipeline->Init(m_window->width, m_window->height);
	m_gamePipeline = m_renderInterface->InstantiateDefaultGraphicPipeline();
	m_gamePipeline->Init(m_window->width, m_window->height);

	Core::Serializer serializer;
	serializer.DeserializeSceneFromFile(&m_scene, "Assets/Scenes/Scene.json");
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