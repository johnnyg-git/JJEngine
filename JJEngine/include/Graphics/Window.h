#ifndef JJENGINE_GRAPHICS_WINDOW_H
#define JJENGINE_GRAPHICS_WINDOW_H

#include <unordered_set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Callbacks
static void WindowErrorCallback(int error, const char* description);
static void WindowResizeCallback(GLFWwindow* window, int width, int height);
static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
static void MouseButtonCallback(GLFWwindow* window, int button, int scanCode, int action, int mods);
static void CursorMoveCallback(GLFWwindow* window, double xPos, double yPos);

typedef void (*ResizeCallback)(GLFWwindow*, int, int);

// Window class
// This class is used to create a window and handle the window's events
class Window {
public:
	// Background color of the window, set when cleared
	glm::vec4 backgroundColor;
private:
	// Title of the window, set at construction
	const char* m_title;
	// Delta time of the window, updated every frame
	double m_deltaTime;
	// Width and height of the window, set at construction
	float m_width, m_height;
	// Mouse position
	float m_mouseX, m_mouseY;
	// Last time the window was updated
	float m_lastTime;
	// Whether the window is destroyed or not
	bool m_destroyed;

	// Pointer to the GLFWWindow instance
	GLFWwindow* m_window;
	// Set of keys that are currently pressed
	std::unordered_set<int> m_keysPressed;
	// Set of mouse buttons that are currently pressed
	std::unordered_set<int> m_mouseButtonsPressed;
	// Vector of functions that are called when the window is resized
	std::vector<ResizeCallback> m_resizeCallbacks;

public:
	// Constructors and destructor
	Window(const char* title, int width, int height);
	Window(const char* title, int width, int height, glm::vec4 backgColor);
	~Window();

	// Add callback to the resize callback vector
	void AddResizeCallback(ResizeCallback callback);

	// Remove callback from the resize callback vector
	void RemoveResizeCallback(ResizeCallback callback);

	// Clears the window, clears color and depth buffer and fills with backgroundColor
	void ClearWindow() const;
	// Updates the window, swaps buffers and polls events
	void UpdateWindow();

	// Checks if a key is pressed, if reset is true, the key will be removed from the pressed keys
	bool IsKeyPressed(int key, bool reset = true);

	// Checks if a mouse button is pressed, if reset is true, the button will be removed from the pressed buttons
	bool IsMouseButtonPressed(int button, bool reset = true);

	// Getters
	inline double GetDeltaTime() const { return m_deltaTime; }
	inline float GetWidth() const { return m_width; }
	inline float GetHeight() const { return m_height; }
	inline float GetMouseX() const { return m_mouseX; }
	inline float GetMouseY() const { return m_mouseY; }
	inline GLFWwindow* GetWindow() const { return m_window; }

private:
	// Initializes the window
	bool Init();

	// Friends
	friend void WindowErrorCallback(int error, const char* description);
	friend void WindowResizeCallback(GLFWwindow* window, int width, int height);
	friend void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	friend void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	friend void CursorMoveCallback(GLFWwindow* window, double xPos, double yPos);
};


#endif