#include "frpch.h"
#include "Renderer.h"

namespace Fracture
{

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::GetRendererAPI();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		s_SceneData->CurrentBoundShader = 0;
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0))
	{
		if (shader->GetHandle() != s_SceneData->CurrentBoundShader)
		{
			shader->Bind();
			s_SceneData->CurrentBoundShader = shader->GetHandle();
		}
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray->GetIndexBuffer()->GetCount());
	}

}