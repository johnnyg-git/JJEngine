#pragma once

namespace JJEngine {
	class Window;


	class Application {
	public:
		static Application* GetInstance() { return s_instance; }

		Application(const char* windowTitle,  bool createConsoleOnDebug = true);
		~Application();

		Window& GetWindow() const { return *m_window; }

		bool IsRunning() const { return m_running; }

	private:
		static Application* s_instance;

		std::unique_ptr<Window> m_window;

		bool m_running;
	};
}