#pragma once
/*!
* @file Texture.h
* @brief Contains the Texture class that is used to store references to textures needed for rendering. Each renderer will have its own implementation of the texture class.
* 
* @see OpenGLTexture
* @see Renderer
* 
* @author Aditya Rajagopal
*/

#include "Fracture\Core\Core.h"

#include <string>
#include <glm\glm.hpp>

namespace Fracture {

	/*!
	* @brief The Texture class is an abstract class that is used to store references to textures needed for rendering. Each renderer will have its own implementation of the texture class.
	*/
	class Texture
	{
	public:
		virtual ~Texture() = default;

		/*!
		* @brief Function that returns the width of the texture.
		* 
		* @return uint32_t: The width of the texture.
		*/
		virtual uint32_t GetWidth() const = 0;

		/*!
		* @brief Function that returns the height of the texture.
		* 
		* @return uint32_t: The height of the texture.
		*/
		virtual uint32_t GetHeight() const = 0;

		/*!
		* @brief Function that returns the handle of the texture.
		* 
		* @return uint32_t: The handle of the texture.
		*/
		virtual uint32_t GetHandle() const = 0;

		/*!
		* @brief Binds the texture to the specified slot.
		* 
		* @param[in] uint32_t slot: The slot to which the texture should be bound.
		*/
		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	/*!
	* @brief The Texture2D class is an abstract class that is used to store references to 2D textures needed for rendering. Each renderer will have its own implementation of the texture class.
	* 
	* @see OpenGLTexture
	* 
	* 
	*/
	class Texture2D : public Texture
	{
	public:
		/*!
		* @brief Function that creates a 2D texture from a given colour and a width and height. The texture will be 4 channel RGBA.
		* 
		* @details We check the renderer api that is being used and create the appropriate 2D texture for that renderer.
		* 
		* @see OpenGLTexture
		* 
		* @param[in] uint32_t width: The width of the texture.
		* @param[in] uint32_t height: The height of the texture.
		* @param[in] glm::vec4 color: The colour of the texture.
		* 
		* @returns A shared pointer to the 2D texture.
		*/
		static Ref<Texture2D> Create(uint32_t width, uint32_t height, glm::vec4 color);

		/*!
		* @brief Function that creates a 2D texture from a given path to an image file.
		* 
		* @details We check the renderer api that is being used and create the appropriate 2D texture for that renderer.
		* 
		* @see OpenGLTexture
		* 
		* @param[in] const std::string& path: The path to the image file.
		* 
		* @returns A shared pointer to the 2D texture.
		*/
		static Ref<Texture2D> Create(const std::string& path);
	};

}

