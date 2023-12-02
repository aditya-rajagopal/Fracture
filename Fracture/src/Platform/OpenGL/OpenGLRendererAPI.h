#pragma once
/*!
* @file OpenGLRendererAPI.h
* 
* @brief Implementation of the RendererAPI for OpenGL
* 
* @see RendererAPI
* 
* @author Aditya Rajagopal
*/

#include "Fracture/Renderer/RendererAPI.h"

namespace Fracture {

	/*!
	* @brief Implementation of the RendererAPI for OpenGL
	*/
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		/*!
		* @brief Constructor for the OpenGLRendererAPI class
		* 
		* @details Calls the Init() function
		* 
		* @see RendererAPI
		* 
		* @todo: Add more states to be set up.
		*/
		OpenGLRendererAPI();
		~OpenGLRendererAPI();

		/*!
		* @brief Function that initializes the OpenGLRendererAPI.
		* 
		* @details Initializes all the OpenGL states that are required for the renderer to work. Currently only enables blending.
		* 
		* @see RendererAPI
		*/
		virtual void Init() override;

		/*!
		* @brief Function that sets the clear color for OpenGL.
		* 
		* @details Calls the glClearColor function to set the clear color for OpenGL.
		* 
		* @param[in] const glm::vec4& color: The color to set the clear color to.
		*/
		virtual void SetClearColor(const glm::vec4& color) override;

		/*!
		* @brief Function that sets the viewport for OpenGL.
		* 
		* @details Calls the glViewport function to set the viewport for OpenGL.
		* 
		* @param[in] uint32_t x: The x coordinate of the viewport.
		* @param[in] uint32_t y: The y coordinate of the viewport.
		* @param[in] uint32_t width: The width of the viewport.
		* @param[in] uint32_t height: The height of the viewport.
		*/
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		/*!
		* @brief Function that clears the screen.
		* 
		* @details Calls the glClear function to clear the screen
		*/
		virtual void Clear() override;

		/*!
		* @brief Function that draws the currently bound vertex array with the currently bound index buffer with the provided index count.
		* 
		* @details Calls glDrawElements with the provided index count.
		* 
		* @param[in] uint32_t indexCount: The number of indices to draw.
		* 
		*/
		virtual void DrawIndexed(uint32_t indexCount = 0) override;

		/*!
		* @brief Checks if the OpenGLRendererAPI is initialized.
		* 
		* @return bool: True if the OpenGLRendererAPI is initialized.
		*/
		virtual bool IsInitialized() const override { return m_IsInitialized; }
	private:
		bool m_IsInitialized = false; /// Flag to check if the OpenGLRendererAPI is initialized.
	};

}
