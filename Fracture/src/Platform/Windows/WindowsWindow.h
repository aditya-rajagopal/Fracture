#pragma once
/*!
* @file WindowsWindow.h
* 
* @brief Contains the WindowsWindow class that is used to create a window for the application.
* 
* @see Window
* 
* @author Aditya Rajagopal
*/


#include "Fracture/Core/Window.h"
#include "Fracture/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Fracture {

	/*!
	* @brief The WindowsWindow class is used to create a window for the application. It owns the renderer context.
	* 
	* @see Window
	*/
	class WindowsWindow : public Window
	{
	public:
		/*!
		* @brief Constructor for the WindowsWindow class
		* 
		* @details Calls the Init() function to initialize the window.
		* 
		* @see Init
		*/
		WindowsWindow(const WindowProperties& props);

		/*!
		* @brief Destructor for the WindowsWindow class
		* 
		* @details Calls the Shutdown() function to shutdown the window.
		* 
		* @see Shutdown
		*/
		virtual ~WindowsWindow();

		/*!
		* @brief Function that updates the window
		* 
		* @details Calls the glfwPollEvents function to poll for events. And then uses the context to swap the buffers.
		*/
		void OnUpdate() override;

		/*!
		* @brief Function that returns the width of the window.
		* 
		* @returns uint32_t: The width of the window.
		*/
		inline uint32_t GetWidth() const override { return m_Data.Width; }

		/*!
		* @brief Function that returns the height of the window.
		* 
		* @returns uint32_t: The height of the window.
		*/
		inline uint32_t GetHeight() const override { return m_Data.Height; }

		/*!
		* @brief Function that sets the event callback function for the window.
		* 
		* @param[in] const EventCallbackFn& callback: The callback function to set.
		* 
		* @see EventCallbackFn
		*/
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		/*!
		* @brief Function that sets the VSync for the window.
		* 
		* @param[in] bool enabled: Whether to enable or disable VSync.
		*/
		void SetVSync(bool enabled) override;

		/*!
		* @brief Function that returns whether VSync is enabled or not.
		* 
		* @returns bool: Whether VSync is enabled or not.
		*/
		bool IsVSync() const override;

		/*!
		* @brief Function that returns a pointer to the native window.
		* 
		* @returns void*: A pointer to the native window.
		*/
		inline virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		/*!
		* @brief Function that initializes the window.
		* 
		* @details Initializes the window using GLFW. Creates the window and the renderer context. Then sets up the event callback function for glfw.
		* 
		* @param[in] const WindowProperties& props: The properties of the window.
		* 
		* @see WindowProperties
		*/
		virtual void Init(const WindowProperties& props);

		/*!
		* @brief Function that shuts down the window.
		* 
		* @details Shuts down the window and the renderer context.
		*/
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window; /// A pointer to the GLFW window.
		Scope<GraphicsContext> m_Context; /// A unique pointer to the renderer context.

		/*!
		* @brief The WindowData struct contains the data of the window that is provided to glfw to set as user data.
		* 
		* @see Window
		* @see glfwSetWindowUserPointer
		* @see glfwGetWindowUserPointer
		* 
		* 
		*/
		struct WindowData
		{
			std::string Title; /// The title of the window.
			uint32_t Width, Height; /// The width and height of the window.
			EventCallbackFn EventCallback; /// The event callback function for the window.
			bool VSync; /// Whether VSync is enabled or not.

			WindowData() = default;
		};

		WindowData m_Data; /// The data of the window that is provided to glfw to set as user data.
	};

}

