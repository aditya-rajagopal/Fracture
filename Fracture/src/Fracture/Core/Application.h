#pragma once
/**
* @file Application.h
* @brief Application header file.
* 
* Contains the Application class and the CreateApplication function. The Application class is the base class for the engine. The application class is responsible for creating the window, running the main loop, and updating the layers.
* 
* The CreateApplication function is used to create the application class in the EntryPoint. This function is defined in the client application.
* 
* @see EntryPoint.h
* @see Window
* @see LayerStack
* @see ImGuiLayer
* @see Event
* 
* @author Aditya Rajagopal
*/


#include "Core.h"
#include "Window.h"

#include "Fracture\Events\Event.h"
#include "Fracture\Events\ApplicationEvent.h"
#include "Fracture\Events\MouseEvent.h"
#include "Fracture\Events\KeyEvent.h"

#include "Fracture\Core\LayerStack.h"
#include "Fracture\ImGui\ImGuiLayer.h"

namespace Fracture {


	/*!
	* @brief The Application class is the base class for the engine. The application class is responsible for creating the window, running the main loop, and updating the layers.
	* 
	* @details The application class is the base class for the engine. The application class is responsible for creating the window, running the main loop, and updating the layers.
	* It also contains the layer stack which is used to store all the layers that are currently active. It handles all the events that are triggered by the window and dispatches them to the appropriate callback functions.
	* There can only be one instance of the application class and it is created in the main function. The application class is a singleton class.
	* 
	* @see Window
	* @see LayerStack
	* 
	*/
	class FRACTURE_API Application
	{
	public:
		/*!
		* @brief This is a constructor for the application class.
		* 
		* @details The constructor will create a window object, set the event callback function to the OnEvent function in the application class, and initialize the Renderer.
		* 
		* @see Window
		* @see Renderer
		* 
		* @see OnEvent
		*/
		Application();
		virtual ~Application() = default;

		/*!
		* @brief This is a function that is the main loop of the application.
		* 
		* @details The function will run the main loop of the application. The function will update the layers in the layer stack and render the ImGui UI.
		* The function will also poll for events and dispatch them to the appropriate callback functions. In the future this function will also update the physics engine.
		* 
		* @see LayerStack
		* @see ImGuiLayer
		* @see Event
		* @see Window
		* @see Renderer
		* 
		*/
		void Run();

		/*!
		* @brief This is a function that will be called when an event is triggered.
		* 
		* @details The function will be called when an event is triggered. The function will then dispatch the events to the appropriate callback functions.
		* Currently it is only triggered by the window events(windows close/resize, key events, and mouse events, etc.).
		* 
		* @see Event
		* @see WindowResizeEvent
		* @see WindowCloseEvent
		* @see MouseScrolledEvent
		* @see MouseMovedEvent
		* @see MouseButtonPressedEvent
		* @see MouseButtonReleasedEvent
		* @see KeyPressedEvent
		* @see KeyReleasedEvent
		* @see KeyTypedEvent
		*/
		void OnEvent(Event& e);

		/*!
		* @brief This is a function that will push a layer onto the application layer stack.
		* 
		* @details The function will push a layer onto the application layer stack. The layer is added to the first half of the stack.
		* layers will be updated in the order they are added to the stack. So this layer will be updated first in the order they were pushed.
		* 
		* @see Layer
		* @see LayerStack
		* 
		* @param[in] Layer* layer - a pointer to the layer that will be pushed onto the stack.
		*/
		void PushLayer(Layer* layer);

		/*!
		* @brief This is a function that will push an overlay onto the application layer stack.
		* 
		* @details The function will push an overlay onto the application layer stack. The overlay is added to the second half of the stack.
		* layers will be updated in the order they are added to the stack. So this overlay will be updated last in the order they were pushed.
		* 
		* @see Layer
		* @see LayerStack
		* 
		* @param[in] Layer* layer - a pointer to the overlay that will be pushed onto the stack.
		*/
		void PushOverlay(Layer* layer);

		/*!
		* @brief This is a function that will return a reference to the window.
		* @see Window
		* @return Window& - returns a reference to the current window.
		*/
		inline Window& GetWindow() { return *m_Window; } 


		/*!
		* @brief This is a static function that will return a reference to the application class.
		* @see Application
		* @return Application& - returns a reference to the static instance of the application.
		*/
		inline static Application& Get() { return *s_Instance; } 
	private:
		/*!
		* @brief This is a boolean function that will be called when the window is closed.
		* 
		* @details The function will set the running boolean to false and return true. This will stop the application from running.
		* 
		* @param[in] WindowCloseEvent& e - a reference to the window close event.
		* @return bool - returns true if the window close event is handled here false if it needs to continue to be propogated.
		*/
		bool OnWindowClose(WindowCloseEvent& e);

		/*!
		* @brief This is a boolean function that will be called when the window is resized.
		* 
		* @details The function will check if the window is minimized and if it is it will return false. If the window is not minimized it will call the OnWindowResize function in the renderer class.
		* 
		* @param[in] WindowResizeEvent& e - a reference to the window resize event.
		* @return bool - returns true if the window resize event is handled here false if it needs to continue to be propogated.
		*/
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		/*! 
		* @brief A unique pointer to a window object tha is managed by the application class.
		* 
		* @details this is a unique pointer to a window object because we only want one window object in our application class and we want to manage it ourselves. 
		* When the application class is destroyed the window object will be destroyed as well
		* 
		* @see Window
		*/
		Ref<Window> m_Window; 

		/// The application layer stack. This will store all the layers that are currently active and will be updated every frame.
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer; /// A pointer to the ImGuiLayer object that is managed by the application class. This is used to render the ImGui UI.

		bool m_Running = true; /// this is a boolean that will be used to determine if the application is running or not.
		bool m_isMinimized = false; /// this is a boolean that will be used to determine if the application is minimized or not.

		long long m_LastFrameTime = 0; /// Stores the start time of the last frame. Used to calculate the delta time.
	private:
		static Application* s_Instance; /// this is a static pointer to the application class.This is used to get the application class from anywhere in the program.
	};

	// To be defined in CLIENT
	Application* CreateApplication();
} // namespace Fracture

