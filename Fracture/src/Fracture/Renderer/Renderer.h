#pragma once

#include "Fracture/Core/Core.h"
#include "Fracture/Renderer/RenderCommand.h"
#include "Fracture/Renderer/RendererAPI.h"

#include "Fracture\Renderer\VertexArray.h"
#include "Fracture\Renderer\Shader.h"

namespace Fracture
{

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}