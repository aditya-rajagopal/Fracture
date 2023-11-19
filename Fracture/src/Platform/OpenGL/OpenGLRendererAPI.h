#pragma once

#include "Fracture/Renderer/RendererAPI.h"

namespace Fracture {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI();
		~OpenGLRendererAPI();

		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(uint32_t indexCount = 0) override;
	};

}
