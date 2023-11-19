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
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
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