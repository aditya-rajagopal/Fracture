#pragma once

#include <string>

namespace Fracture
{
	class Shader
	{
	public:

		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertex_source, const std::string fragment_source);
	};

}
