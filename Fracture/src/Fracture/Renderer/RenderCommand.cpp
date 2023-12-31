#include "frpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Fracture {

	Scope<RendererAPI> RenderCommand::CreateRendererAPI() {
		switch (RendererAPI::GetAPI()) {
			case RendererAPI::API::None: FR_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}

		FR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}