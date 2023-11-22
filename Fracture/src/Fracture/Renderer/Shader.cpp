#include "frpch.h"

#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Fracture
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertex_source, const std::string fragment_source)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    FR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertex_source, fragment_source);
		}

		FR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& shaderFilePath)
	{
		std::filesystem::path path = shaderFilePath;
		std::string name = path.stem().string();

		return Create(name, shaderFilePath);
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& shaderFilePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    FR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, shaderFilePath);
		}

		FR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	void ShaderLibrary::Init()
	{

	}

	void ShaderLibrary::IAdd(const std::string& name, const Ref<Shader>& shader)
	{
		if (m_Shaders.find(name) != m_Shaders.end())
		{
			FR_CORE_WARN("Shader {0} already exists in the library", name);
			return;
		}
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::IAdd(const Ref<Shader>& shader)
	{
		std::string name = shader->GetName();
		if (name.empty())
		{
			FR_CORE_ASSERT(false, "Shader has no name!");
			return;
		}
		if (m_Shaders.find(name) != m_Shaders.end())
		{
			FR_CORE_WARN("Shader {0} already exists in the library", name);
			return;
		}
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::ILoad(const std::string& filepath)
	{
		std::filesystem::path path = filepath;
		std::string name = path.stem().string();

		if (m_Shaders.find(name) != m_Shaders.end())
		{
			FR_CORE_WARN("Shader with name {0} already exists in the library. Use Get with {0} or use Load(name, path)", name);
			return m_Shaders[name];
		}

		Ref<Shader> shader = Shader::Create(filepath);
		IAdd(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::ILoad(const std::string& name, const std::string& filepath)
	{
		if (m_Shaders.find(name) != m_Shaders.end())
		{
			FR_CORE_WARN("Shader with name {0} already exists in the library. Use Get with {0} or provide a different name", name);
			return m_Shaders[name];
		}
		Ref<Shader> shader = Shader::Create(filepath);
		IAdd(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::ILoad(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		if (m_Shaders.find(name) != m_Shaders.end())
		{
			FR_CORE_WARN("Shader with name {0} already exists in the library. Use Get with {0} or provide a different name", name);
			return m_Shaders[name];
		}
		Ref<Shader> shader = Shader::Create(vertexSrc, fragmentSrc);
		IAdd(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::IGet(const std::string& name)
	{
		if (m_Shaders.find(name) == m_Shaders.end())
		{
			FR_CORE_WARN("Shader with name {0} does not exist in the library", name);
			return nullptr;
		}
		return m_Shaders[name];
	}

}
