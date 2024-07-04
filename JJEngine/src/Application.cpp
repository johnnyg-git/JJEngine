#include <iostream>
#include <windows.h>

#include "JJEngine/Application.h"
#include "JJEngine/Window.h"

namespace JJEngine {
	Application* Application::s_instance = nullptr;

	Application::Application(const char* windowTitle, bool createConsoleOnDebug)
	{
		if(s_instance != nullptr)
			throw std::runtime_error("Application already exists");

		#ifdef _DEBUG
		if(createConsoleOnDebug) 
		{
			AllocConsole();

			FILE *fDummy;
			freopen_s(&fDummy, "CONIN$", "r", stdin);
			freopen_s(&fDummy, "CONOUT$", "w", stderr);
			freopen_s(&fDummy, "CONOUT$", "w", stdout);
		}
#endif

		m_window = std::make_unique<Window>(windowTitle, 500, 500);

		s_instance = this;
	}

	Application::~Application()
	{
		std::cout << "Destroying application" << std::endl;

		m_window.reset();

		if(s_instance == this)
			s_instance = nullptr;
	}

}
