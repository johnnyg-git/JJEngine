#include <JJEngine.h>

void main()
{
	Window* gameWindow = new Window("JJENgine Example", 500, 500);
	GLFWwindow* window = gameWindow->GetWindow();

	while (!glfwWindowShouldClose(window))
	{
		gameWindow->ClearWindow();
		gameWindow->UpdateWindow();
	}

	delete gameWindow;
}