#pragma once
/*!
* @file Component.h
* @brief Contians all the components that can be attached to an entity
* 
* @todo: The system currently does not support ECS style component system. This will be implemented in the future.
* 
* @author Aditya Rajagopal
*/

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\quaternion.hpp>

namespace Fracture {

	class TransformComponent
	{
	public:
		/*!
		* @brief Constructor for the TransformComponent class.
		*/
		TransformComponent() = default;

		/*!
		* @brief Copy Constructor for the TransformComponent class.
		*/
		TransformComponent(const TransformComponent&) = default;

		/*!
		* @brief Constructor for the TransformComponent class that takes in a position vector.
		* 
		* @param[in] const glm::vec3& translation: The position vector of the transform.
		*/
		TransformComponent(const glm::vec3& translation)
			: m_Position(translation) {}

		/*!
		* @brief Getter for a const reference to the position vector of the transform.
		* 
		* @return glm::vec3& The position vector of the transform.
		*/
		const glm::vec3& GetPosition() { return m_Position; }

		/*!
		* @brief Getter for a const reference to the rotation vector of the transform.
		* 
		* @return glm::vec3& The rotation vector of the transform.
		*/
		const glm::vec3& GetRotation() { return m_Rotation; }

		/*!
		* @brief Getter for a const reference to the scale vector of the transform.
		* 
		* @return glm::vec3& The scale vector of the transform.
		*/
		const glm::vec3& GetScale() { return m_Scale; }

		/*!
		* @brief Setter for the position vector of the transform. This will set the isChanged flag to true so that the transform matrix can be recalculated.
		* 
		* @param[in] const glm::vec3& position: The position vector of the transform.
		*/
		void SetPosition(const glm::vec3& position) { m_Position = position; isChanged = true; }

		/*!
		* @brief Setter for the rotation vector of the transform. This will set the isChanged flag to true so that the transform matrix can be recalculated.
		* 
		* @param[in] const glm::vec3& rotation: The rotation vector of the transform.
		*/
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; isChanged = true; }

		/*!
		* @brief Setter for the scale vector of the transform. This will set the isChanged flag to true so that the transform matrix can be recalculated.
		* 
		* @param[in] const glm::vec3& scale: The scale vector of the transform.
		*/
		void SetScale(const glm::vec3& scale) { m_Scale = scale; isChanged = true; }

		/*!
		* @brief Function that will translate the transform by the given translation vector. This will set the isChanged flag to true so that the transform matrix can be recalculated.
		* 
		* @param[in] const glm::vec3& translation: The translation vector.
		*/
		void Translate(const glm::vec3& translation) { m_Position += translation; isChanged = true; }

		/*!
		* @brief Function that will add the given rotation to the current rotation. This will set the isChanged flag to true so that the transform matrix can be recalculated.
		* 
		* @param[in] const glm::vec3& rotation: The rotation vector.
		*/
		void Rotate(const glm::vec3& rotation) { m_Rotation += rotation; isChanged = true; }

		/*!
		* @brief Function that will scale the transform by the given scale vector. This will set the isChanged flag to true so that the transform matrix can be recalculated.
		* 
		* @param[in] const glm::vec3& scale: The scale vector.
		*/
		void Scale(const glm::vec3& scale) { m_Scale += scale; isChanged = true; }


		/*!
		* @brief Function that will return the transform matrix of the transformComponent.
		* 
		* @details If the isChanged flag is true then the transform matrix will be recalculated and the isChanged flag will be set to false. If not it will return the cached transform matrix.
		* 
		* @return glm::mat4 The transform matrix of the transformComponent.
		*/
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

		/*!
		* @brief Function that will return the inverse transform matrix of the transformComponent.
		* 
		* @details If the isChanged flag is true then the inverse transform matrix will be recalculated and the isChanged flag will be set to false. If not it will return the cached inverse transform matrix.
		* 
		* @return glm::mat4 The inverse transform matrix of the transformComponent.
		*/
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
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f }; /// The position vector of the transform
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f }; /// The rotation vector of the transform
		glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f }; /// The scale vector of the transform
		bool isChanged = true; /// A boolean flag that will be set to true if the transform is changed and needs to be recalculated

		glm::mat4 m_Transform = glm::mat4(1.0f); /// The cached transform matrix of the transform
		glm::mat4 m_InverseTransform = glm::mat4(1.0f); /// The cached inverse transform matrix of the transform
	};


}