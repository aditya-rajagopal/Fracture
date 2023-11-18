#pragma once

#include <string>

namespace Fracture
{
	class Shader
	{
	public:
		Shader(const std::string& vertex_source, const std::string fragment_source);

		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};

}
