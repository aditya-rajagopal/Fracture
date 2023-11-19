#pragma once


#include "Fracture\Renderer\RendererAPI.h"

namespace Fracture{

	class RenderCommand
	{
	public:
		inline static void DrawIndexed(uint32_t indexCount)
		{
			s_RendererAPI->DrawIndexed(indexCount);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
	private:
		static RendererAPI* CreateRendererAPI();
	private:
		static RendererAPI* s_RendererAPI;
	};

}