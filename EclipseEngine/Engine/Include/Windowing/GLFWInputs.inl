#pragma once

#include "Inputs.hpp"
#include <GLFW/glfw3.h>
#include <array>

inline int CastGlfwKeyCode(KEY_CODE _code)
{
	int index = (int)_code;

	// Create a static array inside the function. This allows the array to be created only once no matter where it's used.
	static const std::array<int, static_cast<size_t>(KEY_CODE::COUNT)> glfwKeyCode =
	{
		GLFW_KEY_A,
		GLFW_KEY_B,
		GLFW_KEY_C,
		GLFW_KEY_D,
		GLFW_KEY_E,
		GLFW_KEY_F,
		GLFW_KEY_G,
		GLFW_KEY_H,
		GLFW_KEY_I,
		GLFW_KEY_J,
		GLFW_KEY_K,
		GLFW_KEY_L,
		GLFW_KEY_M,
		GLFW_KEY_N,
		GLFW_KEY_O,
		GLFW_KEY_P,
		GLFW_KEY_Q,
		GLFW_KEY_R,
		GLFW_KEY_S,
		GLFW_KEY_T,
		GLFW_KEY_U,
		GLFW_KEY_V,
		GLFW_KEY_W,
		GLFW_KEY_X,
		GLFW_KEY_Y,
		GLFW_KEY_Z,
		GLFW_KEY_0,
		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_4,
		GLFW_KEY_5,
		GLFW_KEY_6,
		GLFW_KEY_7,
		GLFW_KEY_8,
		GLFW_KEY_9,
		GLFW_KEY_ESCAPE,
		GLFW_KEY_ENTER,
		GLFW_KEY_SPACE,
		GLFW_KEY_UP,
		GLFW_KEY_DOWN,
		GLFW_KEY_LEFT,
		GLFW_KEY_RIGHT
	};

	return glfwKeyCode[index];
}

inline int CastGlfwMouseCode(MOUSE_CODE _code)
{
	int index = (int)_code;

	// Create a static array inside the function. This allows the array to be created only once no matter where it's used.
	static const std::array<int, static_cast<size_t>(MOUSE_CODE::COUNT)> glfwMouseCode =
	{
		GLFW_MOUSE_BUTTON_LEFT,
		GLFW_MOUSE_BUTTON_MIDDLE,
		GLFW_MOUSE_BUTTON_RIGHT
	};

	return glfwMouseCode[index];
}

inline int CastGlfwCursorMode(CURSOR_MODE _mode)
{
	int index = (int)_mode;

	// Create a static array inside the function. This allows the array to be created only once no matter where it's used.
	static const std::array<int, static_cast<size_t>(CURSOR_MODE::COUNT)> glfwCursorMode =
	{
		GLFW_CURSOR_NORMAL,
		GLFW_CURSOR_HIDDEN,
		GLFW_CURSOR_DISABLED
	};

	return glfwCursorMode[index];
}