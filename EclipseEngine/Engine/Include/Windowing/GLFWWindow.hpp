#pragma once

#include "IWindow.hpp"
#include <GLFW/glfw3.h>

class GLFWWindow : public IWindow
{
	GLFWwindow* m_window = nullptr;

public:
	void CreateWindow(const char* _name, int _width, int _height) override;
	void SetFrameBufferSizeCallback() override;
	float GetTime() override;
	bool WindowShouldClose() override;
	void SetWindowShouldClose(bool _bShouldClose) override;
	void SwapBuffers() override;
	void PollEvents() override;
	void DestroyWindow() override;
    void UpdateInputs() override;
	bool GetKey(KEY_CODE _code, INPUT_ACTION _action) override;
	bool GetMouseButton(MOUSE_CODE _code, INPUT_ACTION _action) override;
	Math::Vec2 GetCursorPos() override;
	void SetCursorPos(Math::Vec2 _pos) override;
	void SetCursorMode(CURSOR_MODE _mode) override;
	inline GLFWwindow* GetWindow() { return m_window; }

	inline virtual GLFWWindow* CastGLFW() { return this; }
};