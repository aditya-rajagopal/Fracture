#pragma once

#include <Fracture\Components\Component.h>
#include <glm\glm.hpp>

namespace Fracture {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera();

		void SetProjection(float left, float right, float bottom, float top);
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		
		const glm::mat4& GetViewMatrix() { return m_CameraTransform.GetTransformInverse(); }
		const glm::mat4& GetViewProjectionMatrix()
		{ 
			if (isChanged)
			{
				m_ViewProjectionMatrix = m_ProjectionMatrix * m_CameraTransform.GetTransformInverse();
				isChanged = false;
			}
			return m_ViewProjectionMatrix;
		}

		const glm::vec3& GetPosition() const { return m_CameraTransform.GetPosition(); }
		void SetPosition(const glm::vec3& position) { m_CameraTransform.SetPosition(position); isChanged = true; }

		float GetRotation() const { return m_CameraTransform.GetRotation().z; }
		void SetRotation(float rotation) { m_CameraTransform.SetRotation({0.0, 0.0, rotation}); isChanged = true;}
		
		void Translate(const glm::vec3& translation) { m_CameraTransform.Translate(translation); isChanged = true; }
		void Rotate(float rotation) { m_CameraTransform.Rotate({ 0.0, 0.0, rotation }); isChanged = true; }

		TransformComponent& GetCameraTransform() { return m_CameraTransform; }
		void SetCameraTransform(const TransformComponent& transform) { m_CameraTransform = transform; isChanged = true; }
	private:
		glm::mat4 m_ProjectionMatrix;
		TransformComponent m_CameraTransform;
		glm::mat4 m_ViewProjectionMatrix;
		bool isChanged;
	};

}

