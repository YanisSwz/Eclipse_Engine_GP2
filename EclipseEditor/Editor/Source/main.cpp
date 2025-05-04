#define NOGDI
#include <windows.h>
#undef CreateWindow

#include "EditorApp.hpp"
#ifndef NDEBUG
#include <crtdbg.h>
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	(void)(hInstance);
	(void)(hPrevInstance);
	(void)(lpCmdLine);
	(void)(nCmdShow);

	/// Used for memory leak debug.
	#ifndef NDEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(1629);
	#endif

	EditorApp editorApp { "Eclipse Engine", 1280, 720 };

	while (!editorApp.ShouldClose())
	{
		editorApp.Update();
		editorApp.Render();
	}

	editorApp.Destroy();
	return 0;
}