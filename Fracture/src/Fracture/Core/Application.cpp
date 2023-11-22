#include "frpch.h"

#include "Application.h"

#include "Fracture\Renderer\Shader.h"
#include "Fracture\Renderer\RenderCommand.h"
#include "Fracture\Renderer\Renderer.h"

#include "Fracture\Input\Input.h"
#include "Fracture\Input\KeyCodes.h"


namespace Fracture {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Scope<Window>(Window::Create()); // we cant use make_unique because we want to use the Create function
		m_Window->SetEventCallback(FRACTURE_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
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

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_isMinimized = true;
			return false;
		}

		m_isMinimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(FRACTURE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(FRACTURE_BIND_EVENT_FN(Application::OnWindowResize));

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
		FR_BEGIN_PROFILE_SESSION("Runtime", "../Logs/FractureProfile-Runtime.json");
		while (m_Running)
		{
			static uint32_t frameCount = 0;

			auto m_StartTimepoint = std::chrono::high_resolution_clock::now();
			long long startTime = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			Timestep deltaTime = (startTime - m_LastFrameTime) / 1000.0f / 1000.0f;
			m_LastFrameTime = startTime;

			if(frameCount == 0)
			{
				deltaTime = 0.0000001f;
			}

			std::string profile_name = "Fracture::Application::Run() Frame " + std::to_string(frameCount);
			// TODO : The scops are not working correctly.
			FR_PROFILE_SCOPE(profile_name.c_str());

			{ // Rendering
				FR_PROFILE_SCOPE("Rendering");
			}

			{ // Layer updates
				FR_PROFILE_SCOPE("LayerStack::OnUpdate");
				// Call the OnUpdate function of all the layers
				if (!m_isMinimized)
				{
					for (Layer* layer : m_LayerStack)
					{
						layer->OnUpdate(deltaTime);
					}
				}
			}

			{ // ImGui rendering
				FR_PROFILE_SCOPE("ImGuiLayer::Rendering");
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			{ // Window updates
				FR_PROFILE_SCOPE("Window::OnUpdate");
				// Call the OnUpdate function of the window
				m_Window->OnUpdate();
			}

			auto endTimepoint = std::chrono::high_resolution_clock::now();
			long long endTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			//FR_CORE_INFO("Frame: {0} Frame time: {1}", frameCount, endTime - startTime);

			frameCount++;
		}
		FR_END_PROFILE_SESSION();
	}


}