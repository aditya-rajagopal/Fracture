#include "frpch.h"

#include "Application.h"

#include <GLFW\glfw3.h>

namespace Fracture {

	#define FRACTURE_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create()); // we cant use make_unique because we want to use the Create function
		m_Window->SetEventCallback(FRACTURE_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(FRACTURE_BIND_EVENT_FN(Application::OnWindowClose));
		FR_CORE_INFO("{0}", e);
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