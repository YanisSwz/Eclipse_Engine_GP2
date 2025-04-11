#include "EditorApp.hpp"

//#ifndef NDEBUG
//#include <crtdbg.h>
//#endif

int main()
{
	/// Used for memory leak debug.
//#ifndef NDEBUG
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetBreakAlloc(28633);
//#endif

	EditorApp editorApp{"Eclipse Engine", 1280, 720};

	while (!editorApp.ShouldClose())
	{
		editorApp.Update();
		editorApp.Render();
	}
	editorApp.Destroy();
	return 0;
}