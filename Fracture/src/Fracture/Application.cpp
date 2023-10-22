#include "frpch.h"

#include "Application.h"

#include <GLFW\glfw3.h>

namespace Fracture {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create()); // we cant use make_unique because we want to use the Create function
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		//FR_BEGIN_PROFILE_SESSION("Application::Run", "FractureProfile-Runtime.json");
		while (m_Running)
		{
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // debug clear color
			glClear(GL_COLOR_BUFFER_BIT);
			// Call the OnUpdate function of the window
			m_Window->OnUpdate();
		}
		//FR_END_PROFILE_SESSION();
	}

}