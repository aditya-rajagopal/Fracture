#include "frpch.h"

#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Fracture
{
	Ref<Shader> Shader::Create(const std::string& vertex_source, const std::string fragment_source)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    FR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(vertex_source, fragment_source);
		}

		FR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}	

}
