#include "frpch.h"

#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Fracture
{
	Shader* Shader::Create(const std::string& vertex_source, const std::string fragment_source)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    FR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLShader(vertex_source, fragment_source);
		}

		FR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}	

}
