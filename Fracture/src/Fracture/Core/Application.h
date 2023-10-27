#pragma once

#include "Core.h"
#include "Window.h"

#include "Fracture\Events\Event.h"
#include "Fracture\Events\ApplicationEvent.h"
#include "Fracture\Events\MouseEvent.h"
#include "Fracture\Events\KeyEvent.h"

#include "Fracture\Core\LayerStack.h"
#include "Fracture\ImGui\ImGuiLayer.h"


namespace Fracture {

	class FRACTURE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; } // this is a reference to the window object that we created in the application class.

		inline static Application& Get() { return *s_Instance; } // this is a static function that returns the application class. This is used to get the application class from anywhere in the program.
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window; // this is a unique pointer to a window object because we only want one window object in our application class and we want to manage it ourselves. When the application class is destroyed the window object will be destroyed as well.
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true; // this is a boolean that will be used to determine if the application is running or not.

		uint32_t m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance; // this is a static pointer to the application class. This is used to get the application class from anywhere in the program.
	};

	// To be defined in CLIENT
	Application* CreateApplication();
} // namespace Fracture

