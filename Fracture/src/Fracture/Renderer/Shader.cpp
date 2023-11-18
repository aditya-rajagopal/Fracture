#include "frpch.h"

#include "Shader.h"
#include "glad\glad.h"

namespace Fracture
{
	static void CompileShaders(uint32_t handle, const std::string& source)
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
			FR_CORE_ASSERT(false, "Shader compilation failed")
		}
	}

	Shader::Shader(const std::string& vertex_source, const std::string fragment_source):
		m_RendererID(0)
	{
		// Create handles for the vertex and framgent shaders
		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


		CompileShaders(vertexShader, vertex_source);
		CompileShaders(fragmentShader, fragment_source);

		m_RendererID = glCreateProgram();
		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);

		// check for linking errors
		int isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			FR_CORE_ERROR("{0}", infoLog.data());
			FR_CORE_ASSERT(false, "Program compilation failed")
			// In this simple program, we'll just leave
		}

		// Detatch shader after successful link
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);

	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	

}
