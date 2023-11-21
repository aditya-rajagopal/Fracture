#include "frpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Fracture {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path):
		m_Path(path), m_RendererID(0)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		FR_CORE_ASSERT(data, "Failed to load image: {}", path);
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		FR_CORE_ASSERT(internalFormat & dataFormat, "Format not supported");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// First paramter is the renderrID of the texture
		// Second paramter is the mipmap level which we are settign
		// Third paramter is the x offset. We can use this to set a partial texture
		// Fourth paramter is the y offset. We can use this to set a partial texture
		// Fifth paramter is the width of the texture we are setting
		// Sixth paramter is the height of the texture we are setting
		// Seventh paramter is the format of the pixel data we are passing in. This is the same as the format we specified when we created the texture
		// Eighth paramter is the data type of the pixel data we are passing in. This is the same as the data type we specified when we created the texture. stbi_uc is unsigned char so we use GL_UNSIGNED_BYTE
		// Ninth paramter is the actual pixel data
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, glm::vec4 color) :
		m_Width(width), m_Height(height), m_Path("None"), m_RendererID(0)
	{
		stbi_uc* data = new stbi_uc[m_Width * m_Height * 4];
		// set each pixel in the iamge to color
		for (int i = 0; i < m_Width * m_Height; i++)
		{
			data[i * 4 + 0] = color.r * 255;
			data[i * 4 + 1] = color.g * 255;
			data[i * 4 + 2] = color.b * 255;
			data[i * 4 + 3] = color.a * 255;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);

		delete[] data;
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		// First paramter is the slot we want to bind the texture to
		// Second paramter is the texture we want to bind
		glBindTextureUnit(slot, m_RendererID);
	}

}