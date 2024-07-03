#include <stdexcept>
#include <iostream>

#include "glad/glad.h"
#include "JJEngine/Window.h"

namespace JJEngine {
	std::vector<Window*> Window::s_windows;

	static void WindowResizeCallback(GLFWwindow* glfwWindow, int width, int height)
	{
		for(auto& window : Window::s_windows)
		{
			if(window->m_glfwWindow == glfwWindow)
			{
				window->m_width = width;
				window->m_height = height;
			}
		}
	}

	Window::Window(const char* title, int width, int height, glm::vec4 backgroundColor)
		: m_title(title), m_width(width), m_height(height), m_backgroundColor(backgroundColor)
	{
		if(!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if(!m_glfwWindow)
		{
			throw std::runtime_error("Failed to create GLFW window");
			return;
		}

		glfwMakeContextCurrent(m_glfwWindow);
		glfwSetWindowUserPointer(m_glfwWindow, this);

		glfwSetWindowSizeCallback(m_glfwWindow, WindowResizeCallback);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSwapInterval(1);

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);

		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);

		s_windows.push_back(this);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_glfwWindow);

		glfwTerminate();
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Window::Update()
	{
		glfwSwapBuffers(m_glfwWindow);
		glfwPollEvents();
	}

	void Window::SetTitle(const char* title)
	{
		glfwSetWindowTitle(m_glfwWindow, title);
		m_title = title;
	}

	void Window::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_glfwWindow, width, height);
		m_width = width;
		m_height = height;
	}

	void Window::SetBackgroundColor(glm::vec4 color)
	{
		m_backgroundColor = color;
		glClearColor(color.x, color.y, color.z, color.w);

	}
}
