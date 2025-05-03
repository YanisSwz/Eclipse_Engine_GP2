#pragma once
#include "Scene.hpp"
#include "SceneCamera.hpp"
#include "GUI/DockingGUI.hpp"
#include "GUI/InspectorGUI.hpp"
#include "GUI/HierarchyGUI.hpp"
#include "GUI/SceneGUI.hpp"
#include "GUI/ConsoleGUI.hpp"
#include "GUI/ContentBrowserGUI.hpp"
#include "GUI/GameGUI.hpp"

namespace Windowing
{
	class IWindow;
}

namespace RHI
{
	class IRenderInterface;
}

class EditorApp
{
public:
	EditorApp(const char* _windowName = "", int _width = 0, int _height = 0);
	~EditorApp();

	bool ShouldClose();
	void Update();
	void Render();
	void Destroy();

private:
	int m_width = 0;
	int m_height = 0;

	int m_sceneWindowWidth = 0;
	int m_sceneWindowHeight = 0;
	int m_sceneWindowPosX = 0;
	int m_sceneWindowPosY = 0;

	int m_gameWindowWidth = 0;
	int m_gameWindowHeight = 0;

	float deltaTime = 0.f;
	float oldTime = 0.f;

	Windowing::IWindow* m_window = nullptr;
	RHI::IRenderInterface* m_renderInterface = nullptr;
	RHI::IGraphicPipeline* m_editorPipeline = nullptr;
	RHI::IGraphicPipeline* m_gamePipeline = nullptr;

	Core::Scene m_scene;
	Core::SceneCamera m_sceneCamera{ 60.f, 0.1f, 100.f };

	Core::GameObject* m_crtGOSelected = nullptr;

	// GUI
	GUI::DockingGUI m_dockingGUI;
	GUI::HierarchyGUI m_hierarchyGUI;
	GUI::InspectorGUI m_inspectorGUI;
	GUI::SceneGUI m_sceneGUI;
	GUI::ConsoleGUI m_consoleGUI;
	GUI::ContentBrowseGUI m_contentBrowserGUI;
	GUI::GameGUI m_gameGUI;

	bool bIsHierarchieWindowEnabled = true;
	bool bIsInspectorWindowEnabled = true;
	bool bIsSceneWindowEnabled = true;
	bool bIsConsoleWindowEnabled = true;
	bool bIsContentBrowserWindowEnabled = true;
	bool bIsGameWindowEnabled = true;

	void InitWindowing(const char* _windowName);
	void InitRHI();
	void InitGUI();
	void LoadScene();

	void DrawScene();
	void PickObjectID();

	void DestroyScene();
	void DestroyGUI();
};