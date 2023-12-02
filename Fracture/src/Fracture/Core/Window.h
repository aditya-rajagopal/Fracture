#pragma once
/*!
* @file Window.h
* @brief Window header file containing the Window class and the WindowProperties struct.
* 
* @see Window
* @see WindowProperties
* @see Application
* 
* @author Aditya Rajagopal
*/

#include "frpch.h"

#include "Fracture\Core\Core.h"
#include "Fracture\Events\Event.h"

namespace Fracture {

	/*!
	* @brief Stores the necessary information for a window.
	*/
	struct WindowProperties
	{
		std::string Title; /// The title of the window
		uint32_t Width; /// The width of the window
		uint32_t Height; /// The height of the window

		/*!
		* @brief Constructor for the WindowProperties struct.
		* 
		* @param[in] const std::string& title: The title of the window.
		* @param[in] uint32_t width: The width of the window.
		* @param[in] uint32_t height: The height of the window.
		*/
		WindowProperties(const std::string& title = "Fracture Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			:Title(title), Width(width), Height(height)
		{
		}
	};

	/*!
	* @brief Window interface representing a desktop system based Window. This is an abstract class.
	*/
	class FRACTURE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>; /// Defines a type for the event callback function. This is a function that takes an event as a parameter and returns void.

		virtual ~Window() {}

		/*!
		* @brief The function that will be called every frame by the application. Must be implemented by the platform specific window class.
		*/
		virtual void OnUpdate() = 0;

		/*!
		* @brief Function that will return the width of the window. Must be implemented by the platform specific window class.
		* 
		* @return uint32_t: The width of the window. Must be implemented by the platform specific window class.
		*/
		virtual uint32_t GetWidth() const = 0;

		/*!
		* @brief Function that will return the height of the window.
		* 
		* @return uint32_t: The height of the window.
		*/
		virtual uint32_t GetHeight() const = 0;

		/*!
		* @brief Function that must be implemented by the platform specific window class. This function will set the event callback function.
		* 
		* @param[in] const EventCallbackFn& callback: The event callback function.
		*/
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		/*!
		* @brief Function that must be implemented by the platform specific window class. This function will set the VSync flag.
		* 
		* @param[in] bool enabled: The VSync flag
		*/
		virtual void SetVSync(bool enabled) = 0;

		/*!
		* @brief Function that must be implemented by the platform specific window class. This function will return the VSync flag.
		*/
		virtual bool IsVSync() const = 0;

		/*!
		* @brief Function that will create a window. This function will create a window based on the platform that the application is running on.
		* 
		* @todo: Currently this only creates a WindowsWindow. In the future we will have to check the platform and create the appropriate window.
		* 
		* @see WindowsWindow
		* 
		* @param[in] const WindowProperties& properties: The properties of the window that you want to create.
		*/
		static Window* Create(const WindowProperties& properties = WindowProperties());
		
		/*!
		* @brief This is a function that will return a void pointer to the window object. This is used to get the window object from anywhere in the program.
		* 
		* @details The reason we return a void pointer is this could technically be any window not necessarily a GLFW window.
		* 
		* @return void*: A void pointer to the window object.
		*/
		virtual void* GetNativeWindow() const = 0;
	};

}

