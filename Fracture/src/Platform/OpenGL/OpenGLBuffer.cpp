#include "frpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Fracture {


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// VertexBuffer ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size):
		m_RendererID(0)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		SetData((void*)vertices, size);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);// copy the vertex data into the buffer's memory by calling glBufferData with the vertex buffer object bound to GL_ARRAY_BUFFER. The fourth argument specifies how we want the graphics card to manage the given data. We have 3 options:
																					// GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
																					// GL_DYNAMIC_DRAW: the data is likely to change a lot.
																					// GL_STREAM_DRAW: the data will change every time it is drawn.
																					// We want to draw the triangle only once, so we'll use GL_STATIC_DRAW.
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// IndexBuffer ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count):
		m_RendererID(0),  m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		SetData((void*)indices, count * sizeof(uint32_t));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::SetData(const void* data, uint32_t size)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // copy the index data into the buffer's memory by calling glBufferData with the index buffer object bound to GL_ELEMENT_ARRAY_BUFFER. We use GL_STATIC_DRAW because the index data will not change.
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}