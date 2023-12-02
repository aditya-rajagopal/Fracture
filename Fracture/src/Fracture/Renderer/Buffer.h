#pragma once
/*!
* @file Buffer.h
* @brief Contains the Buffer class that is used to store the vertex and index buffers.
* 
* @see OpenGLVertexBuffer
* @see OpenGLIndexBuffer
* 
* @author Aditya Rajagopal
*/

#include <string>
#include <vector>

#include "Fracture/Core/Core.h"

namespace Fracture {
	
	/*!
	* @brief The ShaderDataType enum is used to store the data type of the vertex buffer layout.
	*/
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	/*!
	* @brief The ShaderDataTypeSize function is used to return the size of the data type of the vertex buffer layout.
	*/
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float2: return		4 * 2;
			case ShaderDataType::Float: return		4;
			case ShaderDataType::Float3: return		4 * 3;
			case ShaderDataType::Float4: return		4 * 4;
			case ShaderDataType::Mat3: return		4 * 3 * 3;
			case ShaderDataType::Mat4: return		4 * 4 * 4;
			case ShaderDataType::Int: return		4;
			case ShaderDataType::Int2: return		4 * 2;
			case ShaderDataType::Int3: return		4 * 3;
			case ShaderDataType::Int4: return		4 * 4;
			case ShaderDataType::Bool: return		4;
		}

		FR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	/*!
	* @brief The BufferElement struct is used to store the elements of the vertex buffer layout.
	* 
	* @see BufferLayout
	*/
	struct BufferElement
	{
		std::string Name; /// The name of the element
		uint32_t Offset; /// The offset of the element in the vertex buffer layout
		uint32_t Size; /// The size of the element in the vertex buffer layout in bytes
		ShaderDataType Type; /// The data type of the element in the vertex buffer layout
		bool Normalized; /// Whether the element is normalized or not

		/*!
		* @brief Default constructor for the BufferElement struct.
		*/
		BufferElement() = default;

		/*!
		* @brief Constructor for the BufferElement struct. Takes the data type, name and whether the element is normalized or not as parameters.
		* 
		* @param[in] ShaderDataType type: The data type of the element in the vertex buffer layout.
		* @param[in] const std::string& name: The name of the element.
		* @param[in] bool normalized: Whether the element is normalized or not.
		*/
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{}

		/*!
		* @brief Function that returns the number of elements in a specific data type.
		*/
		uint32_t GetElementCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float2: return		2;
				case ShaderDataType::Float: return		1;
				case ShaderDataType::Float3: return		3;
				case ShaderDataType::Float4: return		4;
				case ShaderDataType::Mat3: return		3 * 3;
				case ShaderDataType::Mat4: return		4 * 4;
				case ShaderDataType::Int: return		1;
				case ShaderDataType::Int2: return		2;
				case ShaderDataType::Int3: return		3;
				case ShaderDataType::Int4: return		4;
				case ShaderDataType::Bool: return		1;
			}

			FR_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	/*!
	* @brief The BufferLayout class is used to store the layout of the vertex buffer. Each vertex buffer has a buffer layout.
	* 
	* @see VertexBuffer
	*/
	class BufferLayout {
	public:
		/*!
		* @brief Default constructor for the BufferLayout class.
		*/
		BufferLayout() {}

		/*!
		* @brief Constructor for the BufferLayout class. Takes a vector of elements as a parameter.
		* 
		* @param[in] const std::vector<BufferElement>& elements: The vector of elements.
		*/
		BufferLayout(const std::initializer_list<BufferElement>& elements):
			m_Elements(elements)
		{
			// When you want to initialise buffer layout with a list of elements you need an initializer list of 
			// initializer list of elements. There are 2 implicit conversions here. First, the initializer list of
			// elements is converted to a vector of elements. Second, the initializer list of vectors is converted
			// to a vector of vector of elements. If we want to provide an api like
			// BufferLayout layout = { { ShaderDataType::Float3, "a_Position" }, { ShaderDataType::Float2, "a_TexCoord" } };
			// we need to provide a constructor that takes an initializer list of elements.
			CalculateOffsetsAndStride();
		}

		/*!
		* @brief function that returns an iterator to the beginning of the vector of elements.
		* 
		* @return std::vector<BufferElement>::iterator: An iterator to the beginning of the vector of elements.
		*/
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }

		/*!
		* @brief function that returns an iterator to the end of the vector of elements.
		* 
		* @return std::vector<BufferElement>::iterator: An iterator to the end of the vector of elements.
		*/
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		/*!
		* @brief a const iterator to the beginning of the vector of elements. For use with const objects.
		* 
		* @return std::vector<BufferElement>::const_iterator: A const iterator to the beginning of the vector of elements.
		*/
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }

		/*!
		* @brief a const iterator to the end of the vector of elements. For use with const objects.
		* 
		* @return std::vector<BufferElement>::const_iterator: A const iterator to the end of the vector of elements.
		*/
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		/*!
		* @brief function that returns the size of the vertex buffer layout in bytes.
		*/
		inline uint32_t GetStride() const { return m_Stride; }

		/*!
		* @brief function that returns the vector of elements in the vertex buffer layout.
		* 
		* @return const std::vector<BufferElement>&: The vector of elements in the vertex buffer layout.
		*/
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	private:
		/*!
		* @brief Function that calculates the offsets and stride of the vertex buffer layout.
		* 
		* @details Calculates the offset of each element in the order they are stored in the vector of elements. Also calculates the stride of the vertex buffer layout.
		*/
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements; /// Vector of elements in the buffer layout
		uint32_t m_Stride = 0; /// The stride of the vertex buffer layout in bytes

	};

	/*!
	* @brief The VertexBuffer class is an abstract class that is used to store the vertex buffer. Each renderer will have its own implementation of the vertex buffer.
	* 
	* @see OpenGLVertexBuffer
	* @see BufferLayout
	*/
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		

		/*!
		* @brief Function that creates a vertex buffer. This function will create a vertex buffer based on the platform that the application is running on.
		* 
		* @details We check the renderer api that is being used and create the appropriate vertex buffer for that renderer.
		* 
		* @see OpenGLVertexBuffer
		* 
		* @param[in] float* vertices: The vertex data of the vertex buffer.
		* @param[in] uint32_t size: The size of the vertex buffer.
		* 
		* @returns A shared pointer to the vertex buffer.
		*/
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);

	};

	/*!
	* @brief The IndexBuffer class is an abstract class that is used to store the index buffer. Each renderer will have its own implementation of the index buffer.
	* 
	* @see OpenGLIndexBuffer
	*/
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
		
		/*!
		* @brief Function that creates an index buffer. This function will create an index buffer based on the platform that the application is running on.
		* 
		* @details We check the renderer api that is being used and create the appropriate index buffer for that renderer.
		* 
		* @todo: Currently only supports uint32_t indices. We need to add support for other types of indices.
		* 
		* @see OpenGLIndexBuffer
		* 
		* @param[in] uint32_t* indices: The indices of the index buffer.
		* @param[in] uint32_t size: The size of the index buffer.
		* 
		* @returns A shared pointer to the index buffer.
		*/
		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);
	};
}
