#pragma once
/*!
* @file RendererAPI.h
* @brief Provides an interface for the RendererAPI that needs to be implemented by each renderer.
* 
* @see OpenGLRendererAPI
* @see RenderCommand
* 
* @author Aditya Rajagopal
*/

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Fracture {

	/*!
	* @brief The RendererAPI class provides an interface for the RendererAPI that needs to be implemented by each renderer.
	* 
	* @see OpenGLRendererAPI
	* @see RenderCommand
	*/
	class RendererAPI
	{
	public:
		/*!
		* @brief The API enum class defines the different types of APIs that can be used by the renderer.
		*/
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		/*!
		* @brief Function that initializes the renderer API. Must be implemented by each renderer.
		*/
		virtual void Init() = 0;
		/*!
		* @brief Function that sets the clear color of the renderer API. Must be implemented by each renderer.
		* 
		* @param[in] const glm::vec4& color: The color to set the clear color to
		*/
		virtual void SetClearColor(const glm::vec4& color) = 0;

		/*!
		* @brief Function that sets the viewport of the renderer API. Must be implemented by each renderer.
		* 
		* @param[in] uint32_t x: The x coordinate of the viewport
		* @param[in] uint32_t y: The y coordinate of the viewport
		* @param[in] uint32_t width: The width of the viewport
		* @param[in] uint32_t height: The height of the viewport
		*/
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/*!
		* @brief Function that clears the renderer API. Must be implemented by each renderer.
		*/
		virtual void Clear() = 0;

		/*!
		* @brief Indexed draw call. Must be implemented by each renderer.
		* 
		* @details Must draw the index_count number of indices from the currently bound vertex array.
		* 
		* @param[in] uint32_t indexCount: The number of indices to draw
		*/
		virtual void DrawIndexed(uint32_t indexCount = 0) = 0;

		/*!
		* @brief Function that returns the current state of initialization of the renderer API. Must be implemented by each renderer.
		*/
		virtual bool IsInitialized() const = 0;

		/*!
		* @brief Function that returns the current API that is being used by the renderer.
		* 
		* @todo: Provide a way for the api to be set by the user and not be hardcoded.
		* 
		* @returns API: The current API that is being used by the renderer.
		*/
		inline static API GetAPI() 
		{
			static API s_API = API::OpenGL;
			return s_API;
		}
	};

}

