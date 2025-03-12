#include <iostream>
#include "GLFWWindow.hpp"

int main()
{
	IWindow* window = new GLFWWindow;
	window->CreateWindow("Test", 800, 800);
	//window->SetCursorMode(CURSOR_MODE::CURSOR_DISABLED);
	while (!window->WindowShouldClose())
	{
		window->UpdateInputs();
		if (window->GetKey(KEY_ESCAPE, INPUT_PRESS))
		{
			window->SetWindowShouldClose(true);
		}

		//std::cout << window->GetTime() << std::endl;

		window->SwapBuffers();
		window->PollEvents();
	}
	window->DestroyWindow();
	return 0;
}

