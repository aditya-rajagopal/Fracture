#pragma once
/*!
* @file OpenGLTexture.h
* @brief contains the OpenGL implementation of the Texture class
* 
* @see Texture
* 
* @author Aditya Rajagopal
*/
#include "Fracture/Core/Core.h"
#include "Fracture/Renderer/Texture.h"

namespace Fracture
{
	/*!
	* @brief OpenGL implementation of the Texture2D class
	*/
	class OpenGLTexture2D : public Texture2D
	{
	public:
		/*!
		* @brief Constructor for the OpenGLTexture2D class that takes in a path to the texture file.
		* 
		* @details The constructor will create a texture from the image in file path and store the texture on the GPU
		* 
		* @param[in] const std::string& path: The path to the texture file.
		*/
		OpenGLTexture2D(const std::string& path);

		/*!
		* @brief Constructor for the OpenGLTexture2D class that takes in a width, height, and color.
		* 
		* @details Creates an image with the specified width, height, and color and stores it on the GPU as a texture.
		* 
		* @param[in] uint32_t width: The width of the texture.
		* @param[in] uint32_t height: The height of the texture.
		* @param[in] glm::vec4 color: The color of the texture.
		*/
		OpenGLTexture2D(uint32_t width, uint32_t height, glm::vec4 color);

		virtual ~OpenGLTexture2D();

		/*!
		* @brief Function that returns the width of the texture.
		* 
		* @return uint32_t The width of the texture.
		*/
		virtual uint32_t GetWidth() const override { return m_Width; }

		/*!
		* @brief Function that returns the height of the texture.
		* 
		* @return uint32_t The height of the texture.
		*/
		virtual uint32_t GetHeight() const override { return m_Height; }

		/*!
		* @brief Function that returns the handle of the texture.
		* 
		* @return uint32_t The handle of the texture.
		*/
		virtual uint32_t GetHandle() const override { return m_RendererID; }

		/*!
		* @brief Sets the texture data to a specific texture slot.
		* 
		* @param[in] uint32_t slot: The texture slot to bind the texture to.
		*/
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_Path; /// The path to the texture file. Stored for debugging purposes.
		uint32_t m_Width, m_Height; /// The width and height of the texture.
		uint32_t m_RendererID; /// The handle of the texture.
	};
	
}