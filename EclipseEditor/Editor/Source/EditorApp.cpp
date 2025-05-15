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
#include "Core/Particles/ParticleEmitter.hpp"
#include <implot.h>

EditorApp::EditorApp(const char* _windowName, int _width, int _height)
	: m_width(_width),
	m_height(_height)
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Initializing editor...");
	InitWindowing(_windowName);
	InitGUI();
	InitRHI();
	LoadResources();
	Core::GameObject::DeserializeTags("Assets/Settings/Tags.json");
	LoadScene("Scene");
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Editor successfully initialized");

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

	if (m_window->GetMouseButton(Windowing::MOUSE_CODE::MIDDLE_BUTTON, Windowing::INPUT_ACTION::INPUT_PRESS))
		m_crtGOSelected = PickObject();

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
			if (ImGui::MenuItem("Save Scene"))
			{
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "Save");
				SaveScene();
			}
			if (ImGui::MenuItem("Reload Scene"))
			{
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::DEBUG, "Load");
				ReloadScene();
			}
			if (ImGui::MenuItem("Create Scene"))
			{
				bIsNewSceneWindowOpen = true;
			}
			ImGui::EndMenu();
		}

		if (bIsNewSceneWindowOpen)
		{
			ImGui::OpenPopup("Create New Scene");
			ImGui::SetNextWindowSize(ImVec2(250, 150));

		}

		if (ImGui::BeginPopupModal("Create New Scene", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
		{
			bool bIsSceneNameValid = true;
			if (m_newSceneName == "" || m_newSceneName.size() > SCENE_NAME_MAX_SIZE)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
				bIsSceneNameValid = false;
			}
			ImGui::InputText("##NewScene", &m_newSceneName);
			if (!bIsSceneNameValid)
				ImGui::BeginDisabled();
			if (ImGui::Button("Create") && bIsSceneNameValid)
			{
				CreateNewScene();
			}
			if (!bIsSceneNameValid)
			{
				ImGui::EndDisabled();
				ImGui::PopStyleColor();
			}
			
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				bIsNewSceneWindowOpen = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		if (ImGui::BeginMenu("Windows", true))
		{
			ImGui::MenuItem("Hierarchy", "", &bIsHierarchieWindowEnabled);
			ImGui::MenuItem("Inspector", "", &bIsInspectorWindowEnabled);
			ImGui::MenuItem("Scene", "", &bIsSceneWindowEnabled);
			ImGui::MenuItem("Game", "", &bIsGameWindowEnabled);
			ImGui::MenuItem("Content Browser", "", &bIsContentBrowserWindowEnabled);
			ImGui::MenuItem("Console", "", &bIsConsoleWindowEnabled);
			ImGui::MenuItem("Audio Mixer", "", &bIsAudioMixerWindowEnabled);
			ImGui::EndMenu();
		}



		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.f - 55.f);
		GAME_STATE gameState = m_scene.GetState();
		if (gameState == GAME_STATE::STOP)
		{
			// Play Button
			if (m_playBtnTexture == nullptr)
				m_playBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Start.img");

			ImGui::PushStyleColor(ImGuiCol_Border, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.5f, 0.5f, 0.5f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.75f, 0.75f, 0.75f, 1.f });

			if (ImGui::ImageButton("Play", m_playBtnTexture->GetID(), { 25.f, 25.f }))
			{
				m_scene.SetState(GAME_STATE::PLAY);
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Play!");
				ImGui::SetWindowFocus("Game");
				SaveScene();
			}

			ImGui::PopStyleColor(4);
		}
		else
		{
			// Stop Button
			if (m_stopBtnTexture == nullptr)
				m_stopBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Stop.img");

			ImGui::PushStyleColor(ImGuiCol_Border, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.5f, 0.5f, 0.5f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.75f, 0.75f, 0.75f, 1.f });

			if (ImGui::ImageButton("Stop", m_stopBtnTexture->GetID(), { 25.f, 25.f }))
			{
				m_scene.SetState(GAME_STATE::STOP);
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Stop!");
				ImGui::SetWindowFocus("Scene");
				ReloadScene();
			}

			ImGui::PopStyleColor(4);
		}

		if (gameState == GAME_STATE::PAUSE)
		{
			// Resume Button
			if (m_pauseBtnTexture == nullptr)
				m_pauseBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Pause.img");

			ImGui::PushStyleColor(ImGuiCol_Border, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.5f, 0.5f, 0.5f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.75f, 0.75f, 0.75f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.85f, 0.85f, 0.85f, 1.f });

			if (ImGui::ImageButton("Resume", m_pauseBtnTexture->GetID(), { 25.f, 25.f }))
			{
				m_scene.SetState(GAME_STATE::PLAY);
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Resume!");
			}
			ImGui::PopStyleColor(4);
		}
		else
		{
			// Pause Button
			if (m_pauseBtnTexture == nullptr)
				m_pauseBtnTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Pause.img");

			ImGui::PushStyleColor(ImGuiCol_Border, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.5f, 0.5f, 0.5f, 1.f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.75f, 0.75f, 0.75f, 1.f });

			ImGui::BeginDisabled(gameState == GAME_STATE::STOP);
			if (ImGui::ImageButton("Pause", m_pauseBtnTexture->GetID(), { 25.f, 25.f }))
			{
				m_scene.SetState(GAME_STATE::PAUSE);
				Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Pause!");
			}
			ImGui::EndDisabled();
			ImGui::PopStyleColor(4);
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
		Core::GameObject* newGOSelected = m_hierarchyGUI.Draw(&m_scene, m_crtGOSelected, &m_contentBrowserGUI);
		if (newGOSelected)
			m_crtGOSelected = newGOSelected;
	}

	if (bIsInspectorWindowEnabled)
		m_inspectorGUI.Draw(m_crtGOSelected);

	if (bIsSceneWindowEnabled)
	{
		Core::GameObject* gameObjectPicked = nullptr;
		if (m_window->GetMouseButton(Windowing::MOUSE_CODE::LEFT_BUTTON, Windowing::INPUT_ACTION::INPUT_RELEASE))
			gameObjectPicked = PickObject();
		m_sceneGUI.Draw(m_crtGOSelected, gameObjectPicked, &m_sceneCamera, m_editorPipeline->GetFinalTexture(), m_sceneWindowWidth, m_sceneWindowHeight, m_sceneWindowPosX, m_sceneWindowPosY);
	}

	if (bIsGameWindowEnabled)
		m_gameGUI.Draw(m_scene.GetSystemManager()->GetCameraSystem()->GetCurrentCamera(), m_gamePipeline->GetFinalTexture(), m_gameWindowWidth, m_gameWindowHeight);

	if (bIsConsoleWindowEnabled)
		m_consoleGUI.Draw();

	std::string selectedScene;
	if (bIsContentBrowserWindowEnabled)
		selectedScene = m_contentBrowserGUI.Draw();

	if (selectedScene != "")
	{
		SaveScene();
		m_scene.Reset();
		LoadScene(selectedScene);
	}

	if (bIsAudioMixerWindowEnabled)
		m_audioMixerGUI.Draw(m_scene.GetSystemManager()->GetAudioSystem(), deltaTime);

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

	Core::GameObject::SerializeTags("Assets/Settings/Tags.json");

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

void EditorApp::SetupImGuiStyle()
{
	// Fork of Gold style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.4000000059604645f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 4.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(20.0f, 20.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 4.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 2.0f);
	style.FrameRounding = 0.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(10.0f, 2.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 12.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 10.0f;
	style.ScrollbarRounding = 6.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 6.0f;
	style.TabBorderSize = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.f, 0.f, 0.f, 0.f);
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 0.9999985098838806f, 0.9999899864196777f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(1.0f, 1.0f, 1.0f, 0.3607843220233917f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1372549086809158f, 0.1490196138620377f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1372549086809158f, 0.1490196138620377f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.07058823853731155f, 0.07450980693101883f, 0.08627451211214066f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 0.3921568691730499f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.08235294371843338f, 0.07058823853731155f, 0.09019608050584793f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1372549086809158f, 0.1490196138620377f, 0.1764705926179886f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.352889209985733f, 0.3796438276767731f, 0.442060112953186f, 0.9356223344802856f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 0.407843142747879f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.07058823853731155f, 0.07450980693101883f, 0.08627451211214066f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.07058823853731155f, 0.07450980693101883f, 0.08627451211214066f, 0.407843142747879f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.5728514194488525f, 0.377277135848999f, 0.8969957232475281f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.501960813999176f, 0.3019607961177826f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.572549045085907f, 0.3764705955982208f, 0.8980392217636108f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.2078431397676468f, 0.2078431397676468f, 0.2078431397676468f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.1372549086809158f, 0.1490196138620377f, 0.1764705926179886f, 0.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 0.686274528503418f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 0.f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 0.7372549176216125f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.7372549176216125f, 0.0f, 0.7843137383460999f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.7372549176216125f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.7372549176216125f, 0.0f, 0.7843137383460999f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.6627451181411743f, 0.5254902243614197f, 0.8901960849761963f, 0.4705882370471954f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.7960784435272217f, 0.6784313917160034f, 0.9411764740943909f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.0f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 0.3490196168422699f);
}

void EditorApp::InitGUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	io.IniFilename = "Assets/editor.ini";
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/SourceSans3-Medium.ttf", 24);

	SetupImGuiStyle();
	//ImGui::StyleColorsDark();

#ifdef ImGuiImplementGLFW
	ImGui_ImplGlfw_InitForOpenGL(m_window->CastGLFW()->GetWindow(), true);
#endif // ImGuiImplementGLFW

#ifdef ImGuiImplementOpenGL
	ImGui_ImplOpenGL3_Init("#version 330");
#endif // ImGuiImplementOpenGL
}

void EditorApp::LoadResources()
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
}

void EditorApp::LoadScene(std::string _sceneName)
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Loading Scene: %s", _sceneName.c_str());
	std::string directoryPath = "Assets/Scenes/";
	m_scene.SetName(_sceneName);
	m_scene.DeserializeFromFile(directoryPath + _sceneName + ".json");
}

void EditorApp::ReloadScene()
{
	m_scene.Reset();
	LoadScene(m_scene.GetName());
}

void EditorApp::SaveScene()
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Saving Scene: %s", m_scene.GetName().c_str());
	std::string directoryPath = "Assets/Scenes/";
	m_scene.SerializeToFile(directoryPath + m_scene.GetName() + ".json");
}

void EditorApp::CreateNewScene()
{
	Logging::Logger::GetInstance().Log(Logging::PRIORITY::INFO, "Creating new Scene: %s", m_newSceneName.c_str());
	bIsNewSceneWindowOpen = false;
	ImGui::CloseCurrentPopup();
	std::ofstream newSceneFile("Assets/Scenes/" + m_newSceneName + ".json");
	newSceneFile.close();
	m_contentBrowserGUI.AddScene(m_newSceneName);

	SaveScene();
	m_scene.Reset();
	LoadScene(m_newSceneName);

	m_newSceneName = "";
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

Core::GameObject* EditorApp::PickObject()
{
	Math::Vec2 mousePos = m_window->GetCursorPos();
	int mousePosX = static_cast<int>(mousePos.x) - m_sceneWindowPosX;
	int mousePosY = m_sceneWindowHeight - (static_cast<int>(mousePos.y) - (m_sceneWindowPosY - 30)); // -30 for the size of the ImGui window titlebar
	int pickID = m_editorPipeline->PickObjectID(mousePosX, mousePosY);
	return m_scene.GetObjectByID(pickID);;
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

	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}