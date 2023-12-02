#pragma once
/*!
* @file GraphicsContext.h
* @brief Contains the GraphicsContext class that is used to create a graphics context for the application per renderer.
* 
* @see OpenGLContext
* @see Renderer
* 
* @todo: Add VulkanContext
* 
* @author Aditya Rajagopal
*/

namespace Fracture {

	/*!
	* @brief The GraphicsContext class is an abstract class that is used to create a graphics context for the application. Each renderer will have its own implementation of the graphics context.
	* 
	* @see OpenGLContext
	*/
	class FRACTURE_API GraphicsContext
	{
	public:
		/*!
		* @brief Function that initializes the graphics context. Must be implemented by each renderer.
		*/
		virtual void Init() = 0;

		/*!
		* @brief Function that swaps the buffers of the graphics context and dispalys the image to the screen. Must be implemented by each renderer.
		*/
		virtual void SwapBuffers() = 0;
	};

}