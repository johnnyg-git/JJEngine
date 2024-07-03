#pragma once

namespace JJEngine {
	class Application {
	public:
		static Application* GetInstance() { return s_instance; }

		Application();
		~Application();

		bool IsRunning() const { return m_running; }

	private:
		static Application* s_instance;

		bool m_running;
	};
}