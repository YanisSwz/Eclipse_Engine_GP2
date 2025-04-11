#include "EditorApp.hpp"

int main()
{
	EditorApp* editorApp = new EditorApp{"Eclipse Engine", 1280, 720};

	while (!editorApp->ShouldClose())
	{
		editorApp->Update();
		editorApp->Render();
	}

	editorApp->Destroy();
	delete editorApp;
	return 0;
}