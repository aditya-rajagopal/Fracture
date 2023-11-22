#pragma once

#include <Fracture\Components\Component.h>
#include <Fracture\Renderer\OrthographicCamera.h>
#include <Fracture\Utils\Timestep.h>
#include <Fracture\Components\Component.h>

#include <Fracture\Events\ApplicationEvent.h>
#include <Fracture\Events\MouseEvent.h>
#include <Fracture\Events\KeyEvent.h>


#include <glm\glm.hpp>

namespace Fracture {


	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, float enableRotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetAspectRatio() const { return m_AspectRatio; }


		glm::vec3& GetPosition() { return m_CameraTransform.GetPosition(); }
		void SetPosition(const glm::vec3& position) { m_CameraTransform.SetPosition(position); isChanged = true; }
		void Translate(const glm::vec3& translation) { m_CameraTransform.Translate(translation); isChanged = true; }


		float& GetRotation() { return m_CameraTransform.GetRotation().z; }
		void SetRotation(float rotation) { 
			if (m_EnableRotation)
			{
				m_CameraTransform.SetRotation({ 0.0, 0.0, rotation });
				isChanged = true;
			}
		}
		void Rotate(float rotation) {
			if (m_EnableRotation)
			{
				m_CameraTransform.Rotate({ 0.0, 0.0, rotation });
				isChanged = true;
			}
		}

		
		float& GetZoomLevel() { return m_ZoomLevel; }
		void Zoom(float zoom);
		void SetZoom(float zoom);


		TransformComponent GetCameraTransform() { return m_CameraTransform; }
		void SetCameraTransform(const TransformComponent& transform) { m_CameraTransform = transform; isChanged = true; }

		void SetCameraZoomSpeed(float speed) { m_cameraZoomSpeed = speed; }
		void ToggleRotation(bool enable) { m_EnableRotation = enable; }
		void SetMaxZoom(float zoom) { m_MaxZoom = zoom; }
		void SetMinZoom(float zoom) { m_MinZoom = zoom; }

		float& GetCameraZoomSpeed() { return m_cameraZoomSpeed; }
		bool& GetRotationEnabled() { return m_EnableRotation; }
		float& GetMaxZoom() { return m_MaxZoom; }
		float& GetMinZoom() { return m_MinZoom; }

	private:
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);
		bool OnMouseButtonDownEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonUpEvent(MouseButtonReleasedEvent& e);
	private:
		Timestep m_LastFrameTime;

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool m_EnableRotation;
		TransformComponent m_CameraTransform;

		OrthographicCamera m_Camera;

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };
		glm::vec3 m_InitialCameraPosition = { 0.0f, 0.0f, 0.0f };

		float m_MiddleMouseScale = 0.005f;
		float m_cameraTranslationSpeed = 1.0f;
		float m_cameraRotationSpeed = 1.0f;
		float m_cameraZoomSpeed = 40.0f;
		float m_MaxZoom = 100.0f;
		float m_MinZoom = 0.25f;

		bool isChanged = true;
		bool m_canMoveMiddleMouse = false;
	};

}