#pragma once

#include "Core.h"
#include "Fracture\Events\Event.h"
#include "Fracture\Events\ApplicationEvent.h"
#include "Fracture\Events\MouseEvent.h"
#include "Fracture\Events\KeyEvent.h"
#include "Window.h"

namespace Fracture {

	class FRACTURE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window; // this is a unique pointer to a window object because we only want one window object in our application class and we want to manage it ourselves. When the application class is destroyed the window object will be destroyed as well.
		bool m_Running = true; // this is a boolean that will be used to determine if the application is running or not.
	};

	// To be defined in CLIENT
	Application* CreateApplication();
} // namespace Fracture

