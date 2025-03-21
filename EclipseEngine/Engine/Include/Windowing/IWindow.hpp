#pragma once
#include <map>
#include "Inputs.hpp"
#include "Vec2.hpp"

namespace Windowing
{
	class GLFWWindow;

	class IWindow
	{
	protected:
		std::map<KEY_CODE, INPUT_ACTION> m_keys;
		std::map<MOUSE_CODE, INPUT_ACTION> m_mouseButtons;

	public:
		const char* name;
		int width;
		int height;

		virtual void CreateWindow(const char* _name, int _width, int _height) = 0;
		virtual void SetFrameBufferSizeCallback() = 0;
		virtual float GetTime() = 0;
		virtual bool WindowShouldClose() = 0;
		virtual void SetWindowShouldClose(bool _bShouldClose) = 0;
		virtual void SwapBuffers() = 0;
		virtual void PollEvents() = 0;
		virtual void DestroyWindow() = 0;
		virtual void UpdateInputs() = 0;
		virtual bool GetKey(KEY_CODE _code, INPUT_ACTION _action) = 0;
		virtual bool GetMouseButton(MOUSE_CODE _code, INPUT_ACTION _action) = 0;
		virtual Math::Vec2 GetCursorPos() = 0;
		virtual void SetCursorPos(Math::Vec2 _pos) = 0;
		virtual void SetCursorMode(CURSOR_MODE _mode) = 0;
		virtual float GetMouseScrollValue() = 0;

		inline virtual GLFWWindow* CastGLFW() { return nullptr; }
	};
}