#pragma once
/*!
* @file RenderCommand.h
* @brief Contains the RenderCommand class that is used to send commands to the renderer.
* 
* @details The commands are sent to the renderer API that is currently active. The renderer API is created per renderer and inherits from the RendererAPI class that defines the expected interface.
* 
* @see RendererAPI
* @see OpenGLRendererAPI
* 
* @author Aditya Rajagopal
*/

#include "Fracture\Renderer\RendererAPI.h"

namespace Fracture{

	/*!
	* @brief The RenderCommand class is used to send commands to the renderer. It is a thin wrapper around the RendererAPI class.
	*/
	class RenderCommand
	{
	public:

		/*!
		* @brief Function that initializes the renderer API. This function is called once per renderer. It can be used to get current renderer API It is has a static member variable that is initialized once. This is done to be thread safe.
		* 
		* @see RendererAPI
		* 
		* @return Scope<RendererAPI>&: reference to the current renderer API.
		*/
		inline static Scope<RendererAPI>& GetRendererAPI()
		{
			static Scope<RendererAPI> s_RendererAPI = CreateRendererAPI();
			return s_RendererAPI;
		}

		/*!
		* @brief Function that draws calls the DrawIndexed function of the current renderer API. Draws the index_count number of indices from the currently bound vertex array.
		* 
		* @see RendererAPI
		* @see OpenGLRendererAPI
		* 
		* @param[in] uint32_t indexCount: The number of indices to draw.
		*/
		inline static void DrawIndexed(uint32_t indexCount)
		{
			GetRendererAPI()->DrawIndexed(indexCount);
		}

		/*!
		* @brief Function that sets the clear color of the renderer API. Calls the SetClearColor function of the current renderer API.
		*
		* @see RendererAPI
		*
		* @param[in] const glm::vec4& color: The color to set the clear color to.
		*/
		inline static void SetClearColor(const glm::vec4& color)
		{
			GetRendererAPI()->SetClearColor(color);
		}

		/*!
		* @brief Function that sets the viewport of the renderer API. Calls the SetViewport function of the current renderer API.
		* 
		* @details The viewport is the area of the window that the renderer will render to. This is usually called on window resize.
		* 
		* @see RendererAPI
		* 
		* @param[in] uint32_t x: The x coordinate of the viewport.
		* @param[in] uint32_t y: The y coordinate of the viewport.
		* @param[in] uint32_t width: The width of the viewport.
		* @param[in] uint32_t height: The height of the viewport.
		*/
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			GetRendererAPI()->SetViewport(x, y, width, height);
		}

		/*!
		* @brief Function that clears the screen to be ready to show the next frame. Calls the Clear function of the current renderer API.
		* 
		* @see RendererAPI
		*/
		inline static void Clear()
		{
			GetRendererAPI()->Clear();
		}
	private:
		/*!
		* @brief Function that creates the renderer API instance. This function is called once per renderer. It consideres the current renderer set and creates the appropriate renderer API.
		* 
		* @see RendererAPI
		* 
		* @return Scope<RendererAPI>: A unuque pointer to the renderer API.
		*/
		static Scope<RendererAPI> CreateRendererAPI();
	};

}