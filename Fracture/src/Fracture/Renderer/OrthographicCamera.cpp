#include "frpch.h"
#include "OrthographicCamera.h"

namespace Fracture {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top):
		m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f), m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix)
	{
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearval, float farval):
		m_ProjectionMatrix(glm::ortho(left, right, bottom, top, nearval, farval)), m_ViewMatrix(1.0f), m_ViewProjectionMatrix(m_ProjectionMatrix* m_ViewMatrix)
	{
	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}