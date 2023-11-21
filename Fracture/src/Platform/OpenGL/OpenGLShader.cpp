#include "frpch.h"

#include "OpenGLShader.h"
#include "Fracture\Renderer\Shader.h"

#include "glm\gtc\type_ptr.hpp"

namespace Fracture
{
	std::string ReadFile(const std::string& filePath)
	{
		std::ifstream stream(filePath, std::ios::in, std::ios::binary);
		std::string result;

		if (stream)
		{
			// Read the shader file into the string
			stream.seekg(0, std::ios::end); // go to the end of the file
			result.resize(stream.tellg()); // get length of the file
			stream.seekg(0, std::ios::beg); // go to beginning of the file

			stream.read(&result[0], result.size()); // read into string
			stream.close();
		}
		else
		{
			FR_CORE_ERROR("Could not open file {0}", filePath);
		}

		return result;
	}

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "_TYPE_VERTEX_SHADER") return GL_VERTEX_SHADER;
		if (type == "_TYPE_FRAGMENT_SHADER") return GL_FRAGMENT_SHADER;
		if (type == "_TYPE_PIXEL_SHADER") return GL_FRAGMENT_SHADER;

		return 0;
	}

	static std::string ShaderTypeToString(GLenum type)
	{
		switch (type)
		{
			case GL_VERTEX_SHADER: return "_TYPE_VERTEX_SHADER";
			case GL_FRAGMENT_SHADER: return "_TYPE_FRAGMENT_SHADER";
		}

		FR_CORE_ASSERT(false, "Unknown shader type!");
		return "";
	}

	static void CompileShaders(GLuint handle, const std::string& source, GLenum type)
	{
		const char* src = source.c_str();
		glShaderSource(handle, 1, &src, 0);

		// Compile the vertex shader
		glCompileShader(handle);

		int isCompiled = 0;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(handle, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(handle);

			// Use the infoLog as you see fit.

			FR_CORE_ERROR("{0}", infoLog.data());
			std::string error = "Shader compilation failed: " + ShaderTypeToString(type);
			FR_CORE_ASSERT(false, error.c_str())
		}
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* macroToken = "#ifdef";
		size_t macroTokenLength = strlen(macroToken);
		size_t pos = source.find(macroToken, 0); //Start of shader type declaration line

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); // given the position where we found #ifdef, find the first occurence of a new line
			FR_CORE_ASSERT(eol != std::string::npos, "Syntax error"); // if we dont find a new line then we have a syntax error
			size_t begin = pos + macroTokenLength + 1; // start of shader type name (after #ifdef)
			std::string defineString = source.substr(begin, eol - begin); // get the shader type define name
			
			GLenum shaderType = ShaderTypeFromString(defineString); // convert the shader type define name to an enum

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); // start of shader code after shader type declaration line
			pos = source.find(macroToken, nextLinePos); //Start of next shader type declaration line

			if (shaderType == 0)
				continue; // the ifdef was not a shader type define so we skip it
			// we define the shader define at the top to disable all the other shader types and only compile the one we want
			shaderSources[shaderType] = "#version 450 core\n#define " + defineString + "\n" + source;
		}
		for (auto&& [type, source] : shaderSources)
		{
			FR_CORE_INFO("Shader Type: {0}", ShaderTypeToString(type));
			FR_CORE_INFO("{0}", source);
		}
		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		// Create an empty program object with a unique ID
		GLuint program	= glCreateProgram();

		// Create handles for the vertex and framgent shaders
		std::vector<GLenum> glShaderIDs(shaderSources.size());
		int glShaderIDIndex = 0;
		for (auto&& [type, source] : shaderSources)
		{
			GLuint shader = glCreateShader(type);

			// Create an empty shader object with a unique ID
			CompileShaders(shader, source, type);

			// Attach our shaders to our program
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(program);
		// check for linking errors
		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.

			for (auto shaderID: glShaderIDs)
				glDeleteShader(shaderID);

			// Use the infoLog as you see fit.

			FR_CORE_ERROR("{0}", infoLog.data());
			FR_CORE_ASSERT(false, "Program compilation failed")
				// In this simple program, we'll just leave
		}

		for (auto shaderID : glShaderIDs)
			glDetachShader(program, shaderID);

		m_RendererID = program;


	}


	/**
	* OpenGLShader Constructor with a vertex and fragment shader source
	* 
	* This function will create a shader program.
	* 
	* Arguments:
	* vertex_source(const std::string&): The source code for the vertex shader
	* fragment_source(const std::string&): The source code for the fragment shader
	*/
	OpenGLShader::OpenGLShader(const std::string& vertex_source, const std::string fragment_source) :
		m_RendererID(0)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertex_source;
		shaderSources[GL_FRAGMENT_SHADER] = fragment_source;
		Compile(shaderSources);
	}


	/**
	* OpenGLShader Constructor with a shader file path
	* 
	* This function will read the shader file and create a shader program.
	* The vertex shader needs to be defined within a #ifdef _TYPE_VERTEX_SHADER #endif
	* and the fragment shader needs to be defined within a #ifdef _TYPE_FRAGMENT_SHADER #endif
	* 
	* do not include the #version 450 core in the shader file. That will be added by the preprocessor.
	* 
	* Arguments:
	* ShaderFilePath(const std::string&): Path to the shader file
	* 
	*/
	OpenGLShader::OpenGLShader(const std::string& shaderFilePath):
		m_RendererID(0)
	{
		// Create handles for the vertex and framgent shaders
		std::string source = ReadFile(shaderFilePath);

		auto shaderSources = PreProcess(source);

		Compile(shaderSources);

	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetInt2(const std::string& name, const glm::ivec2& values)
	{
		UploadUniformInt2(name, values);
	}

	void OpenGLShader::SetInt3(const std::string& name, const glm::ivec3& values)
	{
		UploadUniformInt3(name, values);
	}

	void OpenGLShader::SetInt4(const std::string& name, const glm::ivec4& values)
	{
		UploadUniformInt4(name, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& values)
	{
		UploadUniformFloat2(name, values);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& values)
	{
		UploadUniformFloat3(name, values);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& values)
	{
		UploadUniformFloat4(name, values);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix)
	{
		UploadUniformMat3(name, matrix);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		UploadUniformMat4(name, matrix);
	}

	void OpenGLShader::SetBool(const std::string& name, bool value)
	{
		UploadUniformBool(name, value);
	}

	int32_t OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];
		m_UniformLocationCache[name] = glGetUniformLocation(m_RendererID, name.c_str());
		return m_UniformLocationCache[name];
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniform1iv(uniformLocation, 1, &value);
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::ivec2& values)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniform2iv(uniformLocation, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::ivec3& values)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniform3iv(uniformLocation, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::ivec4& values)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniform4iv(uniformLocation, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniform1fv(uniformLocation, 1, &value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniform2fv(uniformLocation, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniform3fv(uniformLocation, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniform4fv(uniformLocation, 1, glm::value_ptr(values));
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix)); // Upload the matrix
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix)); // Upload the matrix
		// TODO: Cache locations
		// The first parameter is the location of the uniform we want to set.
		// The second parameter is the number of matrices we want to upload. Here we only want to upload one.
		// The third parameter specifies whether the matrix should be transposed. OpenGL expects matrices to be in column-major order instead of row-major order.
		// The last parameter is the actual data.
	}

	void OpenGLShader::UploadUniformBool(const std::string& name, bool value)
	{
		int32_t uniformLocation = GetUniformLocation(name);
		glUniform1i(uniformLocation, value);
	}

}
