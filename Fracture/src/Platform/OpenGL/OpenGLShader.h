#pragma once
/*!
* @file OpenGLShader.h
* @brief Contains the OpenGL implementation of the Shader class.
* 
* @see Shader
* 
* @author Aditya Rajagopal
*/
#include <string.h>

#include "Fracture/Core/Core.h"
#include "Fracture/Renderer/Shader.h"

#include "glad/glad.h"


namespace Fracture
{
	/*!
	* @brief The OpenGLShader class is an implementation of the Shader class. It is used to create a shader program for the OpenGL renderer.
	*/
	class OpenGLShader : public Shader
	{
	public:
		/*!
		* @brief Constructor for the OpenGLShader class that takes in the name of the shader, the vertex source, and the fragment source.
		* 
		* @param[in] const std::string& name The name of the shader
		* @param[in] const std::string& vertex_source The vertex source of the shader
		* @param[in] const std::string& fragment_source The fragment source of the shader
		* 
		* @see Shader
		*/
		OpenGLShader(const std::string& name, const std::string& vertex_source, const std::string fragment_source);

		/*!
		* @brief Constructor for the OpenGLShader class that takes in the name of the shader and the path to the shader file.
		* 
		* @param[in] const std::string& name The name of the shader
		* @param[in] const std::string& shaderFilePath The path to the shader file
		*/
		OpenGLShader(const std::string& name, const std::string& shaderFilePath);

		/*!
		* @brief Destructor for the OpenGLShader class deletes the shader program.
		*/
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

		virtual const std::string& GetName() const override { return m_Name; }
		virtual const uint32_t& GetHandle() const override { return m_RendererID; }
	private:
		/*!
		* @brief Function to get the location of a uniform from chache or from the shader program.
		* 
		* 
		* @details The function checks if the uniform is in the cache. If it is, then it returns the location of the uniform from the cache. If it is not, then it gets the location of the uniform from the shader program and adds it to the cache.
		* 
		* @param[in] const std::string& name The name of the uniform
		* 
		* @return int32_t The location of the uniform
		*/
		int32_t GetUniformLocation(const std::string& name);

		/*!
		* @brief Preprocess the shader source code to get the shader source code for each shader type.
		* 
		* @param[in] const std::string& source The source code of the shader
		* 
		* @return std::unordered_map<GLenum, std::string> The shader source code for each shader type
		*/
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		/*!
		* @brief Compile the shader program given the shader source code for each shader type.
		* 
		* @param[in] const std::unordered_map<GLenum, std::string>& shaderSources The shader source code for each shader type
		*/
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID; /// The handle to the shader program
		std::string m_Name; /// The name of the shader mostly used for debugging and identification
		std::unordered_map<std::string, int32_t> m_UniformLocationCache; /// The cache of the uniform locations
	};

}