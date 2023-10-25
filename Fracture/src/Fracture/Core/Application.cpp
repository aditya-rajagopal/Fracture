#include "frpch.h"

#include "Application.h"

#include <glad/glad.h>

namespace Fracture {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create()); // we cant use make_unique because we want to use the Create function
		m_Window->SetEventCallback(FRACTURE_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(FRACTURE_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event); // here we do (*--it) because we want to call the OnEvent function of the layer and not the iterator. The -- is needed because the end iterator is not valid we need 1 before that.
			if (event.Handled) // if the event is handled we break the loop because the layer that set handled=true is a blocking layer
			{
				break;
			}
		}
	}

	void Application::Run()
	{
		//FR_BEGIN_PROFILE_SESSION("Runtime", "../Logs/FractureProfile-Runtime.json");
		while (m_Running)
		{
			static uint32_t frameCount = 0;

			//std::string profile_name = "Fracture::Application::Run() Frame " + std::to_string(frameCount);
			// TODO : The scops are not working correctly.
			//FR_PROFILE_SCOPE(profile_name.c_str());

			{
				//FR_PROFILE_SCOPE("Rendering Colour");
				glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // debug clear color
				glClear(GL_COLOR_BUFFER_BIT);
			}

			{
				//FR_PROFILE_SCOPE("LayerStack::OnUpdate");
				// Call the OnUpdate function of all the layers
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate();
				}
			}

			{
				//FR_PROFILE_SCOPE("Window::OnUpdate");
				// Call the OnUpdate function of the window
				m_Window->OnUpdate();
			}

			frameCount++;
		}
		//FR_END_PROFILE_SESSION();
	}


}