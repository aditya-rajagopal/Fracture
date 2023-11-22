#include "frpch.h"
#include "VertexArray.h"

#include "Fracture/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Fracture {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
		}

		FR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}