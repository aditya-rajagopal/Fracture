#pragma once
/*!
* @file VertexArray.h
* @brief Contains the VertexArray class that is used to create a VertexArray object.
* 
* @see VertexBuffer
* @see IndexBuffer
* 
* @author Aditya Rajagopal
*/

#include "Fracture/Renderer/Buffer.h"

namespace Fracture {
	
	/*!
	* @brief The VertexArray class is an abstract class that is used to create a VertexArray object. Each renderer will have its own implementation of the VertexArray class.
	* 
	* @see OpenGLVertexArray
	*/
	class VertexArray {
	public:
		virtual ~VertexArray() {};

		/*!
		* @brief Function that adds a VertexBuffer to the VertexArray. A vertex array can have multiple vertex buffers.
		* 
		* @param[in] const Ref<VertexBuffer>& vertexBuffer: The VertexBuffer to be added to the VertexArray.
		*/
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

		/*!
		* @brief Function that sets the IndexBuffer of the VertexArray.
		* 
		* @param[in] const Ref<IndexBuffer>& indexBuffer: The IndexBuffer to be set to the VertexArray.
		*/
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		/*!
		* @brief Function that binds the VertexArray. This function is called before drawing the VertexArray.
		*/
		virtual void Bind() const = 0;

		/*!
		* @brief Function that unbinds the VertexArray. This function is called after drawing the VertexArray.
		*/
		virtual void Unbind() const = 0;

		/*!
		* @brief Function that returns the IndexBuffer of the VertexArray.
		* 
		* @returns A reference to the IndexBuffer of the VertexArray.
		*/
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		/*!
		* @brief Function that returns the VertexBuffers of the VertexArray.
		* 
		* @returns const std::vector<Ref<VertexBuffer>>&: A reference to the vector of VertexBuffers of the VertexArray.
		*/
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

		/*!
		* @brief Function that creates a VertexArray. This function will create a VertexArray based on the current active renderer.
		* 
		* @details We check the renderer api that is being used and create the appropriate VertexArray for that renderer.
		* 
		* @see OpenGLVertexArray
		* 
		* @returns A shared pointer to the VertexArray.
		*/
		static Ref<VertexArray> Create();

	};
}
