#pragma once
/*!
* @file OpenGLContext.h
* 
* @brief Contains the OpenGLContext class that is used to create a graphics context for the OpenGL renderer.
* 
* @see GraphicsContext
* 
* @author Aditya Rajagopal
*/


#include "Fracture\Renderer\GraphicsContext.h"

struct GLFWwindow; // Forward declaration


namespace Fracture {

	/*!
	* @brief The OpenGLContext class is an implementation of the GraphicsContext class for the OpenGL renderer.
	* 
	* @details The context stores the window handle of the application window. The context is initialized using the glfwMakeContextCurrent function.
	*/
	class OpenGLContext : public GraphicsContext
	{
	public:
		/*!
		* @brief Constructor for the OpenGLContext class.
		* 
		*
		* 
		* @param[in] GLFWwindow* windowHandle: The window handle of the application window.
		* 
		* @see GLFWwindow
		*/
		OpenGLContext(GLFWwindow* windowHandle);

		/*!
		* @brief Function that initializes the OpenGL context. Calls the gladLoadGLLoader function to load the OpenGL function pointers.
		* 
		* @details makes the provided window handle the current context using the glfwMakeContextCurrent function. Sets up the glad OpenGL function pointers.
		* 
		* @see gladLoadGLLoader
		*/
		virtual void Init() override;

		/*!
		* @brief Function that swaps the buffers of the OpenGL context. Calls the glfwSwapBuffers function.
		* 
		* @see glfwSwapBuffers
		*/
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle; /// The window handle of the application window.
	};

}
