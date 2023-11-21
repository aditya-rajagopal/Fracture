#pragma once

#include "Fracture/Renderer/Buffer.h"

namespace Fracture {
	
	class VertexArray {
	public:
		virtual ~VertexArray() {};

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

		static Ref<VertexArray> Create();

	};
}
