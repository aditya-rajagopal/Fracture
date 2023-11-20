#pragma once

#include "Fracture/Core/Core.h"
#include "Fracture/Renderer/RenderCommand.h"
#include "Fracture/Renderer/RendererAPI.h"

#include "Fracture\Renderer\VertexArray.h"
#include "Fracture\Renderer\Shader.h"
#include "Fracture\Renderer\OrthographicCamera.h"

#include <glm/glm.hpp>

namespace Fracture
{

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}