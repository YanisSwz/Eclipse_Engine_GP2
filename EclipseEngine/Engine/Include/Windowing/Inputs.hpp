#pragma once

namespace Windowing
{
	enum class KEY_CODE : int
	{
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_ESCAPE,
		KEY_ENTER,
		KEY_SPACE,
		KEY_ARROW_UP,
		KEY_ARROW_DOWN,
		KEY_ARROW_LEFT,
		KEY_ARROW_RIGHT,
		COUNT
	};

	enum class MOUSE_CODE : int
	{
		LEFT_BUTTON,
		MIDDLE_BUTTON,
		RIGHT_BUTTON,
		COUNT
	};

	enum class INPUT_ACTION : int
	{
		INPUT_UP,
		INPUT_PRESS,
		INPUT_DOWN,
		INPUT_RELEASE,
		COUNT
	};

	enum class CURSOR_MODE : int
	{
		CURSOR_VISIBLE,
		CURSOR_HIDDEN,
		CURSOR_DISABLED,
		COUNT
	};
}