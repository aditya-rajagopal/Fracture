#pragma once

#include <string.h>

#include "Fracture/Core/Core.h"
#include "Fracture/Renderer/Shader.h"

#include "glad/glad.h"


namespace Fracture
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertex_source, const std::string fragment_source);
		OpenGLShader(const std::string& shaderFilePath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetInt2(const std::string& name, const glm::ivec2& values) override;
		virtual void SetInt3(const std::string& name, const glm::ivec3& values) override;
		virtual void SetInt4(const std::string& name, const glm::ivec4& values) override;


		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& values) override;

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void SetBool(const std::string& name, bool value) override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformInt2(const std::string& name, const glm::ivec2& values);
		void UploadUniformInt3(const std::string& name, const glm::ivec3& values);
		void UploadUniformInt4(const std::string& name, const glm::ivec4& values);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		void UploadUniformBool(const std::string& name, bool value);
	private:
		int32_t GetUniformLocation(const std::string& name);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::unordered_map<std::string, int32_t> m_UniformLocationCache;
	};

}