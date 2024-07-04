#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "JJEngine/Window.h"

namespace JJEngine {
	Window* Window::s_instance = nullptr;

	Window::Window(const char* title, int width, int height, glm::vec4 backgroundColor)
		: m_title(title), m_width(width), m_height(height), m_clearColor(backgroundColor)
	{
		if(s_instance!=nullptr)
		{
			throw std::runtime_error("Only one window can be created at a time");
			return;
		}

		if(!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
			return;
		}

		glfwSetErrorCallback([](int error, const char* description)
		{
			std::cerr << "GLFW error: " << description << std::endl;
		});

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		m_glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if(!m_glfwWindow)
		{
			throw std::runtime_error("Failed to create GLFW window");
			return;
		}

		glfwMakeContextCurrent(m_glfwWindow);
		glfwSetWindowUserPointer(m_glfwWindow, this);

		glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* glfwWindow, int width, int height)
		{
			if(Window::s_instance->m_glfwWindow == glfwWindow)
			{
				Window::s_instance->m_width = width;
				Window::s_instance->m_height = height;
			}
		});

		glfwSetFramebufferSizeCallback(m_glfwWindow, [](GLFWwindow* glfwWindow, int width, int height)
		{
			if(Window::s_instance->m_glfwWindow == glfwWindow)
			{
				glViewport(0, 0, width, height);
			}
		});

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSwapInterval(1);

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);

		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);

		s_instance = this;
	}

	Window::~Window()
	{
		std::cout << "Destroying window" << std::endl;

		glfwDestroyWindow(m_glfwWindow);

		glfwTerminate();

		if(s_instance == this)
			s_instance = nullptr;
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

	void Window::SetClearColor(glm::vec4 color)
	{
		m_clearColor = color;
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void Window::SetClearColor(float r, float g, float b, float a)
	{
		SetClearColor(glm::vec4(r, g, b, a));
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_glfwWindow);
	}

}
