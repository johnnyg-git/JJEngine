#include <JJEngine/JJEngine.h>


void main()
{
	Window window("Test App", 500, 500);

	while(!glfwWindowShouldClose(window.GetGLFWWindow()))
	{
		window.Clear();
		window.Update();
	}
}