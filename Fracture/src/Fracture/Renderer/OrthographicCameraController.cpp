#include "frpch.h"
#include "OrthographicCameraController.h"

#include "Fracture\Core\Core.h"
#include "Fracture/Input/Input.h"
#include "Fracture/Input/KeyCodes.h"
#include "Fracture/Input/MouseButtonCodes.h"

namespace Fracture {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float enableRotation) :m_AspectRatio(aspectRatio), m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_EnableRotation(enableRotation)
	{
		//FR_PROFILE_FUNCTION();
		//Fracture::EventDispatcher::Connect<Fracture::MouseButtonPressedEvent>(FR_BIND_EVENT_FN(OrthographicCameraController::OnMouseButtonDownEvent));
	}

	void OrthographicCameraController::OnUpdate(Timestep delta_time)
	{
		m_LastFrameTime = delta_time;
		FR_PROFILE_SCOPE("CameraController::OnUpdate");
		// when middle mouse button is held move camera based on mouse movement based on movement from when it was pressed and stop
		// when it is released.
		if (Fracture::Input::IsMouseButtonPressed(FR_MOUSE_BUTTON_MIDDLE) && m_canMoveMiddleMouse)
		{
			auto [x, y] = Fracture::Input::GetMousePosition();
			glm::vec2 delta = glm::vec2(x, y) - m_InitialMousePosition;

			// the delta.y is negated because the y axis is inverted in screen space
			glm::vec3 updatedPosition = m_InitialCameraPosition + m_MiddleMouseScale * glm::vec3(delta.x, -delta.y, 0.0f);
			SetPosition(updatedPosition);
		}

		if (Fracture::Input::IsKeyPressed(FR_KEY_DOWN))
			Translate(m_cameraTranslationSpeed * delta_time * glm::vec3(-1.0f, -1.0f, 0.0f));
		else if (Fracture::Input::IsKeyPressed(FR_KEY_UP))
			Translate(m_cameraTranslationSpeed * delta_time * glm::vec3(1.0f, 1.0f, 0.0f));

		if (Fracture::Input::IsKeyPressed(FR_KEY_LEFT))
			Translate(m_cameraTranslationSpeed * delta_time * glm::vec3(-1.0f, 1.0f, 0.0f));
		else if (Fracture::Input::IsKeyPressed(FR_KEY_RIGHT))
			Translate(m_cameraTranslationSpeed * delta_time * glm::vec3(1.0f, -1.0f, 0.0f));

		if (m_EnableRotation)
		{
			if (Fracture::Input::IsKeyPressed(FR_KEY_Q))
				Rotate(m_cameraRotationSpeed * delta_time);
			else if (Fracture::Input::IsKeyPressed(FR_KEY_E))
				Rotate(-m_cameraRotationSpeed * delta_time);
		}
		
		if (isChanged)
		{
			m_Camera.SetViewMatrix(m_CameraTransform.GetTransformInverse());
			isChanged = false;
		}

		m_cameraTranslationSpeed = m_ZoomLevel * 2.0f;
		m_cameraRotationSpeed = m_ZoomLevel * 2.0f;
		m_MiddleMouseScale = m_ZoomLevel * 0.005f;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(FRACTURE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(FRACTURE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResizedEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(FRACTURE_BIND_EVENT_FN(OrthographicCameraController::OnMouseButtonDownEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(FRACTURE_BIND_EVENT_FN(OrthographicCameraController::OnMouseButtonUpEvent));
	}

	bool OrthographicCameraController::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		Zoom(-e.GetYOffset() * m_cameraZoomSpeed * m_LastFrameTime);
		return false;
	}

	bool OrthographicCameraController::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnMouseButtonDownEvent(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == FR_MOUSE_BUTTON_MIDDLE)
		{
			m_canMoveMiddleMouse = true;
			auto [x, y] = Fracture::Input::GetMousePosition();
			m_InitialMousePosition = glm::vec2(x, y);
			m_InitialCameraPosition = m_CameraTransform.GetPosition();
		}

		return false;
	}

	bool OrthographicCameraController::OnMouseButtonUpEvent(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == FR_MOUSE_BUTTON_MIDDLE)
		{
			m_canMoveMiddleMouse = false;
		}

		return false;
	}


	void OrthographicCameraController::Zoom(float zoom) {
		m_ZoomLevel += zoom;
		m_ZoomLevel = std::max(m_ZoomLevel, m_MinZoom);
		m_ZoomLevel = std::min(m_ZoomLevel, m_MaxZoom);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void OrthographicCameraController::SetZoom(float zoom) {
		m_ZoomLevel = zoom;
		m_ZoomLevel = std::max(m_ZoomLevel, m_MinZoom);
		m_ZoomLevel = std::min(m_ZoomLevel, m_MaxZoom);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
}