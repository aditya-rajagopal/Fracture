#pragma once
/*!
* @file Shader.h
* @brief Contains the Shader and ShaderLibrary class.
* 
* @see OpenGLShader
* 
* @author Aditya Rajagopal
*/

#include <string>
#include <unordered_map>

#include <glm\glm.hpp>

namespace Fracture
{
	/*!
	* @brief The Shader class is an abstract class that is used to create a shader for the application. Each renderer will have its own implementation of the shader.
	* 
	* @details Each implementation of the shader will have its own renderer ID. The renderer ID is used to identify the shader in the renderer. The implementation should also implement functions to set uniforms in the shader based on the name of the uniform.
	* 
	* @see OpenGLShader
	* 
	* @todo: Add a way to automatically find the uniforms that need to be set in the shader.
	*/
	class Shader
	{
	public:
		virtual ~Shader() {};

		/// @brief Function that binds to be used by the subsequent draw calls.
		virtual void Bind() const = 0;
		/// @brief Function that unbinds the shader.
		virtual void Unbind() const = 0;

		// The following functions set the uniforms in the shader based on the name of the uniform.
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

		/*!
		* @brief Function that creates a shader from 2 strings containing the vertex and fragment shader source code. The shader will be created based on the renderer API that is currently active.
		* 
		* @param[in] const std::string& name: The name of the shader.
		* @param[in] const std::string& vertex_source: The vertex shader source code.
		* @param[in] const std::string& fragment_source: The fragment shader source code.
		* 
		* @return A shared pointer to the shader
		*/
		static Ref<Shader> Create(const std::string& name, const std::string& vertex_source, const std::string fragment_source);

		/*!
		* @brief Function that creates a shader from a file containing the vertex and fragment shader source code. The shader will be created based on the renderer API that is currently active.
		* 
		* @details The requirement for the shader source file is to be a glsl shader. The vertex and framgent shader parts of the shader source file should be contained within a _TYPE_VERTEX_SHADER and _TYPE_FRAGMENT_SHADER block respectively.
		* you can use _TYPE_PIXEL_SHADER instead of _TYPE_FRAGMENT_SHADER.
		* 
		* @param[in] const std::string& name: The name for the shader.
		* @param[in] const std::string& shaderFilePath: The path to the shader source file.
		* 
		* @return A shared pointer to the shader
		*/
		static Ref<Shader> Create(const std::string& name, const std::string& shaderFilePath);

		/*!
		* @brief Function that creates a shader from a file containing the vertex and fragment shader source code. The shader will be created based on the renderer API that is currently active.
		* 
		* @details The requirement for the shader source file is to be a glsl shader. The vertex and framgent shader parts of the shader source file should be contained within a _TYPE_VERTEX_SHADER and _TYPE_FRAGMENT_SHADER block respectively.
		* you can use _TYPE_PIXEL_SHADER instead of _TYPE_FRAGMENT_SHADER. The name of the shader will be the name of the file. 
		* 
		* If the name is repeated it will cause an error. In most situations it is better to use the other Create function that takes in a name and a filepath.
		* 
		* @param[in] const std::string& shaderFilePath: The path to the shader source file.
		* 
		* @return A shared pointer to the shader
		*/
		static Ref<Shader> Create(const std::string& shaderFilePath);

		/*!
		* @brief Function to get the name of the shader. Must be implemented by the platform specific shader class.
		* 
		* @return const std::string&: The name of the shader.
		*/
		virtual const std::string& GetName() const = 0;

		/*!
		* @brief Function to get the handle ID of the shader. Must be implemented by the platform specific shader class.
		* 
		* @return const uint32_t&: The handle ID of the shader.
		*/
		virtual const uint32_t& GetHandle() const = 0;
	};


	/*!
	* @brief The ShaderLibrary class is a singleton class that is used to store all the shaders that are created in the application.
	* 
	* @details The shaders are stored in a map with the name of the shader as the key and the shader reference as the value.
	* 
	* @todo: Add a way to make instances of existing shaders.
	* @todo: Add some default shaders.
	*/
	class ShaderLibrary
	{
	public:

		/*!
		* @brief Function to get the instance of the shader library. This is a singleton class. It has a static member variable that is initialized once. This is done to be thread safe.
		* 
		* @return Scope<ShaderLibrary>&: A reference to the shader library.
		*/
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

		/*!
		* @brief Function to add a shader to the library. The shader will be added to the library with the name of the shader as the key. If the shader with the same name already exists it will cause a warning but will not cause an error. It will not add the shader to the library.
		* 
		* @param[in] const std::string& name: The name of the shader.
		* @param[in] const Ref<Shader>& shader: The shader reference to be added to the library.
		*/
		static void Add(const std::string& name, const Ref<Shader>& shader) { GetInstance()->IAdd(name, shader); }

		/*!
		* @brief Function to add a shader to the library. The the key will be the name of the shader. If the shader with the same name already exists it will cause a warning but will not cause an error. It will not add the shader to the library.
		* 
		* @param[in] const Ref<Shader>& shader: The shader reference to be added to the library.
		*/
		static void Add(const Ref<Shader>& shader) { GetInstance()->IAdd(shader); }

		/*!
		* @brief Function loads a shader from a filepath, intializes it and adds it to the library. The shader will be added to the library with the name of the shader as the filename. If the shader with the same name already exists it will cause a warning but will not cause an error. It will not add the shader to the library.
		* 
		* @param[in] const std::string& filepath: The path to the shader source file.
		* 
		* @return A shared pointer to the shader
		*/
		static Ref<Shader> Load(const std::string& filepath) { return GetInstance()->ILoad(filepath); }

		/*!
		* @brief Function loads a shader from a filepath, intializes it and adds it to the library. The shader will be added to the library with the name provided instead of the filename. If the shader with the same name already exists it will cause a warning but will not cause an error. It will not add the shader to the library.
		* 
		* @param[in] const std::string& name: The name of the shader.
		* @param[in] const std::string& filepath: The path to the shader source file.
		* 
		* @return A shared pointer to the shader
		*/
		static Ref<Shader> Load(const std::string& name, const std::string& filepath) { return GetInstance()->ILoad(name, filepath); }

		/*!
		* @brief Function loads a shader from 2 strings containing the vertex and fragment shader source code, intializes it and adds it to the library. The shader will be added to the library with the name provided. If the shader with the same name already exists it will cause a warning but will not cause an error. It will not add the shader to the library.
		* 
		* @param[in] const std::string& name: The name of the shader.
		* @param[in] const std::string& vertexSrc: The vertex shader source code.
		* @param[in] const std::string& fragmentSrc: The fragment shader source code.
		* 
		* @return A shared pointer to the shader
		*/
		static Ref<Shader> Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) { return GetInstance()->ILoad(name, vertexSrc, fragmentSrc); }

		/*!
		* @brief Function to get a shader from the library. The shader will be retrieved from the library with the name provided. If the shader with the same name does not exist it will return a  nullptr and cause a warning.
		* 
		* @param[in] const std::string& name: The name of the shader to be retrieved.
		* 
		* @return A shared pointer to the shader
		*/
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
		std::unordered_map<std::string, Ref<Shader>> m_Shaders; /// a map of all the shaders we have loaded
	};

}

#define MAX_SHADER_TYPE_COUNT 2 /// the number of shader types we support currently (vertex and fragment shaders)