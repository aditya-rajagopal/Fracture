#pragma once


#include "Fracture\Renderer\RendererAPI.h"

namespace Fracture{

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI = CreateRendererAPI();
			s_RendererAPI->Init();
		}
		inline static void DrawIndexed(uint32_t indexCount)
		{
			s_RendererAPI->DrawIndexed(indexCount);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
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