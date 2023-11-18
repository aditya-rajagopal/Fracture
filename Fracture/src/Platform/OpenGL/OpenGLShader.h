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

		void Bind() const override;
		void Unbind() const override;
	private:
		uint32_t m_RendererID;
	};

}