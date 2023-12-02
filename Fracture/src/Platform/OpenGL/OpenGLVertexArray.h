#pragma once
/*!
* @file OpenGLVertexArray.h
* @brief VertexArray implementation for OpenGL.
* 
* @see VertexArray
* 
* @author Aditya Rajagopal
*/

#include "Fracture\Renderer\VertexArray.h"


namespace Fracture {

	/*!
	* @brief OpenGLVertexArray class that implements the VertexArray class for OpenGL.
	* 
	* @see VertexArray
	*/
	class OpenGLVertexArray: public VertexArray
	{
	public:
		/*!
		* @brief Create a VertexArray object and store the ID in m_RendererID. Binds the VertexArray object.
		*/
		OpenGLVertexArray();

		/*!
		* @brief Destructor for the OpenGLVertexArray class. Deletes the VertexArray object.
		*/
		~OpenGLVertexArray();

		/*!
		* @brief Add a VertexBuffer to the VertexArray object.
		* 
		* @details Binds the vertex buffer to the vertex array state and stores the vertex buffer in the m_VertexBuffers vector. It sets the vertexAttributePointers for the vertex buffer using the vertex buffer layout.
		* 
		* @see VertexBuffer
		* 
		* @param[in] const Ref<VertexBuffer>& vertexBuffer: The vertex buffer to be added to the vertex array.
		*/
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

		/*!
		* @brief Set the IndexBuffer of the VertexArray object.
		* 
		* @details Binds the index buffer to the vertex array state and stores the index buffer in the m_IndexBuffer variable.
		*/
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		/*!
		* @brief Get the IndexBuffer of the VertexArray object.
		* 
		* @returns A reference to the index buffer of the vertex array.
		*/
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

		/*!
		* @brief Gets all the vertex buffers of the vertex array.
		* 
		* @returns A vector of references to the vertex buffers of the vertex array.
		*/
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		/*!
		* @brief Binds the vertex array.
		*/
		virtual void Bind() const override;

		/*!
		* @brief Unbinds the vertex array.
		*/
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererID; /// The ID of the vertex array.
		std::vector<Ref<VertexBuffer>> m_VertexBuffers; /// A vector of vertex buffers.
		Ref<IndexBuffer> m_IndexBuffer; /// The index buffer of the vertex array.
		uint32_t m_VertexBufferIndex = 0; /// The index the current attribute is at this is so we can bind multiple vertex buffers to the vertex array.
	};

}
