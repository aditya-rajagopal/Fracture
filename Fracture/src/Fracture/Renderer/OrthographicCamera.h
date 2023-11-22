#pragma once

#include <Fracture\Components\Component.h>
#include <glm\glm.hpp>

namespace Fracture {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		OrthographicCamera(float left, float right, float bottom, float top, float nearval, float farval);
		~OrthographicCamera();

		void SetProjection(float left, float right, float bottom, float top);
		
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

		void SetProjectionMatrix(const glm::mat4& projection) { m_ProjectionMatrix = projection; m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }
		void SetViewMatrix(const glm::mat4& view) { m_ViewMatrix = view; m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};

}

