#pragma once

#include <string>
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

		static Ref<Shader> Create(const std::string& vertex_source, const std::string fragment_source);
		static Ref<Shader> Create(const std::string& shaderFilePath);
	};

}
