#pragma once

#include "IWindow.hpp"
#include "ProjectExports.hpp"
#include <GLFW/glfw3.h>

namespace Windowing
{
	class GLFWWindow : public IWindow
	{
		GLFWwindow* m_window = nullptr;

	public:
		ECLIPSE_ENGINE void CreateWindow(const char* _name, int _width, int _height) override;
		ECLIPSE_ENGINE void SetFrameBufferSizeCallback() override;
		ECLIPSE_ENGINE float GetTime() override;
		ECLIPSE_ENGINE bool WindowShouldClose() override;
		ECLIPSE_ENGINE void SetWindowShouldClose(bool _bShouldClose) override;
		ECLIPSE_ENGINE void SwapBuffers() override;
		ECLIPSE_ENGINE void PollEvents() override;
		ECLIPSE_ENGINE void DestroyWindow() override;
		ECLIPSE_ENGINE void UpdateInputs() override;
		ECLIPSE_ENGINE bool GetKey(KEY_CODE _code, INPUT_ACTION _action) override;
		ECLIPSE_ENGINE bool GetMouseButton(MOUSE_CODE _code, INPUT_ACTION _action) override;
		ECLIPSE_ENGINE Math::Vec2 GetCursorPos() override;
		ECLIPSE_ENGINE void SetCursorPos(Math::Vec2 _pos) override;
		ECLIPSE_ENGINE void SetCursorMode(CURSOR_MODE _mode) override;
		ECLIPSE_ENGINE inline GLFWwindow* GetWindow() { return m_window; }

		inline virtual GLFWWindow* CastGLFW() { return this; }
	};
}