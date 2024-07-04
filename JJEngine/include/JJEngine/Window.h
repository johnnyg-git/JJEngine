#pragma once

#include "glm/vec4.hpp"


class GLFWwindow;

namespace JJEngine {
	class Window
	{
	public:
		Window(const char* title, int width, int height, glm::vec4 clearColor = glm::vec4(0,0,0,1));
		~Window();

		void Clear();
		void Update();

		// Clear color format: RGBA
		// Range: 0 ~ 1
		glm::vec4 GetClearColor() const { return m_clearColor; }
		void SetClearColor(glm::vec4 color);
		void SetClearColor(float r, float g, float b, float a = 255);

		GLFWwindow* GetGLFWWindow() const { return m_glfwWindow; }

		const char* GetTitle() const { return m_title; }
		void SetTitle(const char* title);

		int GetWidth() const { return m_width;}
		int GetHeight() const { return m_height; }
		void SetSize(int width, int height);

		bool ShouldClose() const;

	private:
		static Window* s_instance;

		glm::vec4 m_clearColor;

		GLFWwindow* m_glfwWindow;

		const char* m_title;

		int m_width, m_height;
	};
}