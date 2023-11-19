#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\quaternion.hpp>

namespace Fracture {

	class TransformComponent
	{
	public:
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: m_Position(translation) {}

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_Scale; }

		void SetPosition(const glm::vec3& position) { m_Position = position; isChanged = true; }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; isChanged = true; }
		void SetScale(const glm::vec3& scale) { m_Scale = scale; isChanged = true; }

		void Translate(const glm::vec3& translation) { m_Position += translation; isChanged = true; }
		void Rotate(const glm::vec3& rotation) { m_Rotation += rotation; isChanged = true; }
		void Scale(const glm::vec3& scale) { m_Scale += scale; isChanged = true; }

		glm::mat4 GetTransform()
		{
			if (isChanged)
			{
				glm::mat4 rotation = glm::toMat4(glm::quat(m_Rotation));
				glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);
				glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);
				m_Transform = translation * rotation * scale;
				isChanged = false;
			}
			return m_Transform;
		}

		glm::mat4 GetTransformInverse()
		{
			if (isChanged)
			{

				glm::mat4 rotation = glm::toMat4(glm::quat(m_Rotation));
				glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);
				glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);
				m_InverseTransform = glm::inverse(translation * rotation * scale);
				isChanged = false;
			}
			return m_InverseTransform;
		}
	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };
		bool isChanged = true;

		glm::mat4 m_Transform = glm::mat4(1.0f);
		glm::mat4 m_InverseTransform = glm::mat4(1.0f);
	};


}