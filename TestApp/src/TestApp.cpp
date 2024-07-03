#include <windows.h>
#include <JJEngine/JJEngine.h>


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	JJEngine::Window window("Test App", 500, 500);

	while(!glfwWindowShouldClose(window.GetGLFWWindow()))
	{
		window.Clear();
		window.Update();
	}

	return 0;
}