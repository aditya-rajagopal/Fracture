#include "frpch.h"
#include "OrthographicCamera.h"

namespace Fracture {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top):
		m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
		isChanged = true;
	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		isChanged = true;
	}

}