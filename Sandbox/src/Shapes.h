#pragma once

#include "Fracture.h"

#include <memory>


namespace Sandbox
{

	struct Object
	{
		Fracture::TransformComponent Transform;
		std::shared_ptr<Fracture::VertexArray> VertexArray;
		std::shared_ptr<Fracture::Shader> Shader;

		glm::vec4 Color = { 1.0, 0.0, 1.0, 1.0 };
		std::string Name;

		Object(const std::string& name, const glm::vec4& color)
			: Name(name), Color(color)
		{
		}

		Object(const std::string& name)
			: Name(name), Color({ 1.0, 0.0, 1.0, 1.0 })
		{
		}

		Object(const std::string& name, const glm::vec4& color, const std::shared_ptr<Fracture::VertexArray>& vertexArray, const std::shared_ptr<Fracture::Shader>& shader)
			: Name(name), Color(color), VertexArray(vertexArray), Shader(shader)
		{
		}

		Object(const std::string& name, const glm::vec4& color, const std::shared_ptr<Fracture::VertexArray>& vertexArray, const std::shared_ptr<Fracture::Shader>& shader, const Fracture::TransformComponent& transform)
			: Name(name), Color(color), VertexArray(vertexArray), Shader(shader), Transform(transform)
		{
		}
	};

}