#include "frpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Fracture {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float2: return		GL_FLOAT;
		case ShaderDataType::Float: return		GL_FLOAT;
		case ShaderDataType::Float3: return		GL_FLOAT;
		case ShaderDataType::Float4: return		GL_FLOAT;
		case ShaderDataType::Mat3: return		GL_FLOAT;
		case ShaderDataType::Mat4: return		GL_FLOAT;
		case ShaderDataType::Int: return		GL_INT;
		case ShaderDataType::Int2: return		GL_INT;
		case ShaderDataType::Int3: return		GL_INT;
		case ShaderDataType::Int4: return		GL_INT;
		case ShaderDataType::Bool: return		GL_BOOL;
		}

		FR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray():
		m_RendererID(0)
	{
		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		const auto& layout = vertexBuffer->GetLayout();
		FR_CORE_ASSERT(layout.GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // This says how the data is layed out in the buffer
																					// 0 is the index of the attribute we want to configure. In the previous line we enabled this index with glEnableVertexAttribArray.
																					// 3 specifies the size of the vertex attribute. The vertex attribute is a vec3 so it is composed of 3 values.
																					// GL_FLOAT specifies the type of the data.
																					// GL_FALSE specifies if we want the data to be normalized. If we set this to GL_TRUE all the data that has a value not between 0 (or -1 for signed data) and 1 will be mapped to those values. This is usually not desired but it can be useful when we store colors as unsigned chars (values between 0 and 255) and we want them to be floats between 0 and 1 (which we do).
																					// 3 * sizeof(float) is the stride. It defines where the next vertex attribute would be 
																					// nullptr is the offset of where the position data begins in the buffer. Since the position data is at the start of the data array this value is 0.

		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(
				m_VertexBufferIndex,
				element.GetElementCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset
			);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
}