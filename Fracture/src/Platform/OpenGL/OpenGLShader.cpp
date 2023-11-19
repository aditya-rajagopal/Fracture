#include "frpch.h"

#include "OpenGLShader.h"
#include "Fracture\Renderer\Shader.h"

#include "glad\glad.h"
#include "glm\gtc\type_ptr.hpp"

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

	OpenGLShader::OpenGLShader(const std::string& vertex_source, const std::string fragment_source) :
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

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int32_t uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix)); // Upload the matrix
		// TODO: Cache locations
		// The first parameter is the location of the uniform we want to set.
		// The second parameter is the number of matrices we want to upload. Here we only want to upload one.
		// The third parameter specifies whether the matrix should be transposed. OpenGL expects matrices to be in column-major order instead of row-major order.
		// The last parameter is the actual data.
	}

}
