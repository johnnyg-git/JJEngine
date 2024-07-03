#pragma once

#include "GLFW/glfw3.h"
#include "glm/vec4.hpp"

namespace JJEngine {
	static void WindowResizeCallback(GLFWwindow* window, int width, int height);


	class Window
	{
	public:
		Window(const char* title, int width, int height, glm::vec4 backgroundColor = glm::vec4(255,255,255,255));
		~Window();

		void Clear();
		void Update();

		const char* GetTitle() const { return m_title; }
		void SetTitle(const char* title);

		int GetWidth() const { return m_width;}
		int GetHeight() const { return m_height; }
		void SetSize(int width, int height);

		glm::vec4 GetBackgroundColor() const { return m_backgroundColor; }
		void SetBackgroundColor(glm::vec4 color);

		GLFWwindow* GetGLFWWindow() const { return m_glfwWindow; }

	private:
		glm::vec4 m_backgroundColor;

		const char* m_title;

		int m_width, m_height;

		GLFWwindow* m_glfwWindow;

		static std::vector<Window*> s_windows;

		friend void WindowResizeCallback(GLFWwindow* window, int width, int height);
	};
}