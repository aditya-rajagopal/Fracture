#include "frpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Fracture {

	OpenGLRendererAPI::OpenGLRendererAPI()
	{
		Init();
	}

	OpenGLRendererAPI::~OpenGLRendererAPI()
	{
	}

	void OpenGLRendererAPI::Init()
	{
		// Enable blending
		glEnable(GL_BLEND);

		// Set the blend function to use alpha blending. Here the first parameter specifies the source factor and the second parameter specifies the destination factor. The source factor specifies how the source color (the color of the fragment that is being rendered) is combined with the destination color (the color that is already in the framebuffer). The destination factor specifies how the destination color is combined with the source color.
		// The possible factors are GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA, and GL_SRC_ALPHA_SATURATE.
		// We use GL_SRC_ALPHA and GL_ONE_MINUS_SRC_ALPHA as the source and destination factors respectively. This means that we take the alpha value of the source fragment (the texture we try to draw) and multiply it by its color. Then we take 1.0 - alpha for the destination fragment (the color that is already in the framebuffer) and multiply it by the color of the source fragment. The result is then added together to form the final color.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Enable depth testing
		//glEnable(GL_DEPTH_TEST);
		//// Accept fragment if it closer to the camera than the former one
		//glDepthFunc(GL_LESS);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CCW);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(uint32_t indexCount)
	{
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr); // draw the triangle
		// GL_TRIANGLES specifies the mode we want to draw in. Other modes include GL_POINTS and GL_LINES.
		// 3 specifies the number of indices we want to draw.
		// GL_UNSIGNED_INT specifies the type of the indices.
		// nullptr is the offset of where the index data begins in the buffer. Since the index data is at the start of the data array this value is 0.

		// we dont need to provide a pointer because we are using the indexbuffer that we bound earlier attached to m_vertexArray. This means that OpenGL already knows where the index buffer is.
		// This is because we bound the index buffer to the vertex array object. This also means that we don't need to bind the index buffer every time we want to draw something. As long as we have the vertex array object bound we can just call glDrawElements and OpenGL will know which index buffer to use.
	}

}