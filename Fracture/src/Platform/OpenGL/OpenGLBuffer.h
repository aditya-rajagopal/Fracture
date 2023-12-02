#pragma once
/*!
* @file OpenGLBuffer.h
* @brief Contains the OpenGLBuffer class that implements the VertexBuffer and IndexBuffer classes for OpenGL.
* 
* @see VertexBuffer
* @see IndexBuffer
* 
* @author Aditya Rajagopal
*/

#include "Fracture/Renderer/Buffer.h"


namespace Fracture {
	
	/*!
	* @brief The OpenGLVertexBuffer class is an implementation of the VertexBuffer class for OpenGL.
	* 
	* @see VertexBuffer
	*/
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		/*!
		* @brief Constructor for the OpenGLVertexBuffer class
		* 
		* @details Creates the buffers, binds it and then sets the data.
		* 
		* @param[in] float* vertices: The vertices of the vertex buffer
		* @param[in] uint32_t size: The size of the vertex buffer
		*/
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		/*!
		* @brief Destructor for the OpenGLVertexBuffer class. Deletes the buffers
		*/
		~OpenGLVertexBuffer();

		/*!
		* @brief Function that sets the data of the vertex buffer.
		* 
		* @details Function assumes the vertex buffer is already bound. 
		* 
		* @todo: Currently the draw call is of type OPENGL_STATIC_DRAW. This needs to be changed to be customizable.
		* 
		* @param[in] void* data: The data to be set in the vertex buffer
		* 
		* @param[in] uint32_t size: The size of the data to be set in the vertex buffer
		*/
		virtual void SetData(const void* data, uint32_t size) override;

		/*!
		* @brief Function that sets the layout of the vertex buffer. This is needed to be used to draw.
		* 
		* @param[in] const BufferLayout& layout: The layout of the vertex buffer
		* 
		* @see BufferLayout
		*/
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		/*!
		* @brief Function that returns the layout of the vertex buffer.
		* 
		* @returns BufferLayout& The layout of the vertex buffer
		*/
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		/*!
		* @brief Function that binds the vertex buffer
		*/
		virtual void Bind() const override;

		/*!
		* @brief Function that unbinds the vertex buffer
		*/
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererID; /// The handle to the vertex buffer
		BufferLayout m_Layout; /// The layout of the vertex buffer
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		virtual void SetData(const void* data, uint32_t size) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}