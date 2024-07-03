#include <stdexcept>

#include "JJEngine/Application.h"

namespace JJEngine {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if(s_instance != nullptr)
			throw std::runtime_error("Application already exists");

		s_instance = this;
	}

	Application::~Application()
	{
		if(s_instance == this)
			s_instance = nullptr;
	}
}
