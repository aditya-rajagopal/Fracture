#pragma once

#include <string>
#include <unordered_map>

#include <glm\glm.hpp>

namespace Fracture
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetInt2(const std::string& name, const glm::ivec2& values) = 0;
		virtual void SetInt3(const std::string& name, const glm::ivec3& values) = 0;
		virtual void SetInt4(const std::string& name, const glm::ivec4& values) = 0;
					 
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& values) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& values) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& values) = 0;
					 
		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;
					 
		virtual void SetBool(const std::string& name, bool value) = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertex_source, const std::string fragment_source);
		static Ref<Shader> Create(const std::string& name, const std::string& shaderFilePath);
		static Ref<Shader> Create(const std::string& shaderFilePath);

		virtual const std::string& GetName() const = 0;
	};

	class ShaderLibrary
	{
	public:

		static Scope<ShaderLibrary>& GetInstance()
		{
			static Scope<ShaderLibrary> instance;
			if (instance == nullptr)
			{
				instance = CreateScope<ShaderLibrary>();
				instance->InitLibrary();
			}
			return instance;
		}

		static void Add(const std::string& name, const Ref<Shader>& shader) { return GetInstance()->IAdd(name, shader); } 
		static void Add(const Ref<Shader>& shader) { return GetInstance()->IAdd(shader); }
		static Ref<Shader> Load(const std::string& filepath) { return GetInstance()->ILoad(filepath); }
		static Ref<Shader> Load(const std::string& name, const std::string& filepath) { return GetInstance()->ILoad(name, filepath); }
		static Ref<Shader> Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) { return GetInstance()->ILoad(name, vertexSrc, fragmentSrc); }
		static Ref<Shader> Get(const std::string& name) { return GetInstance()->IGet(name); }
	private:
		void InitLibrary();
		void IAdd(const std::string& name, const Ref<Shader>& shader); // add a shader to the library
		void IAdd(const Ref<Shader>& shader); // add a shader to the library
		Ref<Shader> ILoad(const std::string& filepath); // load a shader from a file
		Ref<Shader> ILoad(const std::string& name, const std::string& filepath); // load a shader from a file
		Ref<Shader> ILoad(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc); // load shaders from string sources
		Ref<Shader> IGet(const std::string& name); // get a shader from the library
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders; // a map of all the shaders we have loaded
	};

}

#define MAX_SHADER_TYPE_COUNT 2 // the number of shader types we support currently (vertex and fragment shaders)