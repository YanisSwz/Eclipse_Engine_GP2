#pragma once
#include "Scene.hpp"
#include "SceneCamera.hpp"

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

	int m_sceneWidth = 0;
	int m_sceneHeight = 0;
	int m_scenePosX = 0;
	int m_scenePosY = 0;

	float deltaTime = 0.f;
	float oldTime = 0.f;

	Windowing::IWindow* m_window = nullptr;
	RHI::IRenderInterface* m_renderInterface = nullptr;
	RHI::IGraphicPipeline* m_defaultPipeline = nullptr;

	Core::Scene m_scene;
	Core::SceneCamera m_sceneCamera{ 60.f, 0.1f, 100.f };

	Core::GameObject* m_crtGOSelected = nullptr;

	void InitWindowing(const char* _windowName);
	void InitRHI();
	void InitGUI();
	void LoadScene();

	void StartDockSpaceGUI();
	void EndDockSpaceGUI();
	void DrawHierarchyGUI();
	void DrawInspectorGUI();
	void DrawSceneGUI();
	void DrawConsoleGUI();

	void DrawScene();

	void DestroyScene();
	void DestroyGUI();
};