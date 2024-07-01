#include "Graphics/Window.h"

#include <iostream>

// Callbacks
// Error callback, called when error occurs
void WindowErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

// Window resize callback, called when window is resized
void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, (float)width, (float)height);
	Window* wind = (Window*)glfwGetWindowUserPointer(window);
	wind->m_width = width;
	wind->m_height = height;

	for(const auto& callback : wind->m_resizeCallbacks)
		callback(window, width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	Window* wind = (Window*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS)
	{
		wind->m_keysPressed.insert(key);
	}
	else if (action == GLFW_RELEASE)
	{
		wind->m_keysPressed.erase(key);
	}
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Window* wind = (Window*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS)
	{
		wind->m_mouseButtonsPressed.insert(button);
	}
	else if (action == GLFW_RELEASE)
	{
		wind->m_mouseButtonsPressed.erase(button);
	}
}

void CursorMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
	Window* wind = (Window*)glfwGetWindowUserPointer(window);
	wind->m_mouseX = xPos;
	wind->m_mouseY = yPos;
}

// Window class methods

// Window class constructors and destructor
// Default constructor, uses black as background color
Window::Window(const char* title, int width, int height)
{
	// Initialize variables
	m_title = title;
	m_width = width;
	m_height = height;
	// Set background color to black
	backgroundColor = glm::vec4(0, 0, 0, 1);
	// Initialize window, terminate if failed
	if (!Init()) {
		glfwTerminate();
	}
}

// Constructor with custom background color
Window::Window(const char* title, int width, int height, glm::vec4 backgColor)
	: backgroundColor(backgColor), m_title(title), m_width(width), m_height(height), m_destroyed(false)
{
	// Initialize window, terminate if failed
	if (!Init()) {
		glfwTerminate();
	}
}

// Destructor
Window::~Window()
{
	// Destroy window
	if (m_window != nullptr)
		glfwDestroyWindow(m_window);

	m_destroyed = true;

	// Terminate GLFW
	glfwTerminate();
}

void Window::AddResizeCallback(ResizeCallback callback)
{
	m_resizeCallbacks.push_back(callback);
}

void Window::RemoveResizeCallback(ResizeCallback callback)
{
	if(m_destroyed) return;
	m_resizeCallbacks.erase(std::remove(m_resizeCallbacks.begin(), m_resizeCallbacks.end(), callback), m_resizeCallbacks.end());
}

// Initializes the window
// Returns true if successful, false if failed
// Also prints OpenGL version, GLSL version, vendor and renderer
bool Window::Init()
{
	// Set error callback
	glfwSetErrorCallback(WindowErrorCallback);
	// Initialize GLFW, return false if failed
	if (!glfwInit()) {
		std::cout << "Error: \nFailed to initialize GLFW" << std::endl;
		return false;
	}

	// Set OpenGL version to 4.6 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window, return false if failed
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

	// Return false if window creation failed
	if (!m_window) {
		glfwTerminate();
		std::cout << "Error: \nFailed to initialize window" << std::endl;
	}

	// Set window user pointer to this
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);

	// Set window resize callback
	glfwSetFramebufferSizeCallback(m_window, WindowResizeCallback);

	// Load OpenGL functions
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	// Set vsync to 1
	glfwSwapInterval(1);

	// Print OpenGL version, GLSL version, vendor and renderer
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	// Enable depth testing
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glDepthFunc(GL_LEQUAL);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Sets color used to clear color buffers
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);

	// Initialize m_lastTime
	double currentTime = glfwGetTime();
	m_lastTime = currentTime;

	glfwSetKeyCallback(m_window, KeyCallback);
	glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
	glfwSetCursorPosCallback(m_window, CursorMoveCallback);

	m_deltaTime = 0.0f;

	// Done, return true
	return true;
}

// Clears the window, clears color and depth buffer and fills with backgroundColor
void Window::ClearWindow() const
{
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

// Updates the window, swaps buffers, polls events and updates delta time
void Window::UpdateWindow()
{
	// Update delta time
	const double currentTime = glfwGetTime();
	m_deltaTime = currentTime - m_lastTime; m_lastTime = currentTime;

	// Swap buffers and poll events
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

bool Window::IsKeyPressed(int key, bool reset)
{
	if (m_keysPressed.contains(key))
	{
		if (reset)
			m_keysPressed.erase(key);

		return true;
	}

	return false;
}