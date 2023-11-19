#pragma once

#include <string.h>

#include "Fracture/Core/Core.h"
#include "Fracture/Renderer/Shader.h"


namespace Fracture
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertex_source, const std::string fragment_source);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
	private:
		uint32_t m_RendererID;
	};

}