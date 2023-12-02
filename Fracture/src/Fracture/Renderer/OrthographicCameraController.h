#pragma once
/*!
* @file OrthographicCameraController.h
* 
* @brief OrthographicCameraController header file containing the OrthographicCameraController class. This class is used to control the orthographic camera.
* 
* @see OrthographicCamera
* 
* @author Aditya Rajagopal
*/

#include <Fracture\Components\Component.h>
#include <Fracture\Renderer\OrthographicCamera.h>
#include <Fracture\Utils\Helpers.h>
#include <Fracture\Components\Component.h>

#include <Fracture\Events\ApplicationEvent.h>
#include <Fracture\Events\MouseEvent.h>
#include <Fracture\Events\KeyEvent.h>


#include <glm\glm.hpp>

namespace Fracture {

	/*!
	* @brief The OrthographicCameraController class is used to control the orthographic camera.
	* 
	* @see OrthographicCamera
	*/
	class OrthographicCameraController
	{
	public:
		/*!
		* @brief Constructor for the OrthographicCameraController class that takes in the aspect ratio of the window and whether or not the camera should be able to rotate.
		* 
		* @param[in] float aspectRatio The aspect ratio of the window.
		* @param[in] float enableRotation Whether or not the camera should be able to rotate.
		*/
		OrthographicCameraController(float aspectRatio, float enableRotation = false);

		/*!
		* @brief the Update function that is called every frame by layer that owns the OrthographicCameraController.
		* 
		* @param[in] Timestep ts The time passed since the last frame.
		*/
		void OnUpdate(Utils::Timestep ts);

		/*!
		* @brief the OnEvent function that is called by the layer that owns the OrthographicCameraController when an event is triggered.
		* 
		* @param[in] Event& e The event that is triggered.
		*/
		void OnEvent(Event& e);

		/*!
		* @brief Getter for the OrthographicCamera.
		* 
		* @return OrthographicCamera& The reference to OrthographicCamera.
		*/
		OrthographicCamera& GetCamera() { return m_Camera; }

		/*!
		* @brief Getter for the OrthographicCamera to be used by a const OrthographicCameraController.
		* 
		* @return const OrthographicCamera& The const reference to OrthographicCamera.
		*/
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		/*!
		* @brief Getter for the aspect ratio of the window.
		* 
		* @return float The aspect ratio of the window.
		*/
		float GetAspectRatio() const { return m_AspectRatio; }

		/*!
		* @brief Getter for the OrthographicCamera's position.
		* 
		* @return const glm::vec3& The position of the OrthographicCamera.
		*/
		const glm::vec3& GetPosition() { return m_CameraTransform.GetPosition(); }

		/*!
		* @brief Setter for the OrthographicCamera's position. Sets the position of the OrthographicCamera to the position passed in.
		* 
		* @details The function sets the position of the OrthographicCamera to the position passed in and sets the isChanged boolean to true. This will cause the view matrix to be updated in the OnUpdate function.
		* 
		* @param[in] const glm::vec3& position The position that the OrthographicCamera's position will be set to.
		*/
		void SetPosition(const glm::vec3& position) { m_CameraTransform.SetPosition(position); isChanged = true; }

		/*!
		* @brief Translates the OrthographicCamera's position by the translation passed in.
		* 
		* @details The function translates the OrthographicCamera's position by the translation passed in and sets the isChanged boolean to true. This will cause the view matrix to be updated in the OnUpdate function.
		* 
		* @param[in] const glm::vec3& translation The translation that the OrthographicCamera's position will be translated by.
		*/
		void Translate(const glm::vec3& translation) { m_CameraTransform.Translate(translation); isChanged = true; }

		/*!
		* @brief Getter for the OrthographicCamera's rotation.
		* 
		* @return const float& The rotation of the OrthographicCamera returned as a const reference
		*/
		const float& GetRotation() { return m_CameraTransform.GetRotation().z; }

		/*!
		* @brief Setter for the OrthographicCamera's rotation. Sets the rotation of the OrthographicCamera to the rotation passed in if rotation is enabled. Only Z axis roation is supported due to this camera currently being 2D.
		* 
		* @details The function sets the rotation of the OrthographicCamera to the rotation passed in and sets the isChanged boolean to true. This will cause the view matrix to be updated in the OnUpdate function.
		* 
		* @param[in] float rotation The rotation that the OrthographicCamera's rotation will be set to.
		*/
		void SetRotation(float rotation) { 
			if (m_EnableRotation)
			{
				m_CameraTransform.SetRotation({ 0.0, 0.0, rotation });
				isChanged = true;
			}
		}

		/*!
		* @brief Rotates the OrthographicCamera's rotation by the rotation passed in if rotation is enabled. Only Z axis roation is supported due to this camera currently being 2D.
		* 
		* @details The function rotates the OrthographicCamera's rotation by the rotation passed in and sets the isChanged boolean to true. This will cause the view matrix to be updated in the OnUpdate function.
		* 
		* @param[in] float rotation The rotation that the OrthographicCamera's rotation will be rotated by.
		*/
		void Rotate(float rotation) {
			if (m_EnableRotation)
			{
				m_CameraTransform.Rotate({ 0.0, 0.0, rotation });
				isChanged = true;
			}
		}

		/*!
		* @brief Getter for the OrthographicCamera's zoom level.
		* 
		* @return float&: Reference to the zoom level of the OrthographicCamera.
		*/
		float& GetZoomLevel() { return m_ZoomLevel; }

		/*!
		* @brief Setter for the OrthographicCamera's zoom level. Sets the zoom level of the OrthographicCamera to the zoom level passed in.
		* 
		* @details The function adds the given zoom value to the current zoom level clamps the zoom level between m_MinZoom and m_MaxZoom. Then the projection matrix is updated.
		* 
		* @param[in] float zoom The zoom level to be added to the current zoom level.
		*/
		void Zoom(float zoom);

		/*!
		* @brief Setter for the OrthographicCamera's zoom level. Sets the zoom level of the OrthographicCamera to the zoom level passed in.
		* 
		* @details The function sets the zoom level to the zoom level passed in clamps the zoom level between m_MinZoom and m_MaxZoom. Then the projection matrix is updated.
		* 
		* @param[in] float zoom The zoom level to be set to.
		*/
		void SetZoom(float zoom);

		/*!
		* @brief Getter for the OrthographicCamera's transform component. Returns a constant reference to the transform component of the OrthographicCamera.
		* 
		* @return cosnt TransformComponent&: The transform component of the OrthographicCamera.
		*/
		const TransformComponent& GetCameraTransform() { return m_CameraTransform; }

		/*!
		* @brief Setter for the OrthographicCamera's transform component. Sets the transform component of the OrthographicCamera to the transform component passed in. Sets the isChanged boolean to true.
		* 
		* @details the transform component being changed causes the view matrix to be updated in the OnUpdate function.
		* 
		* @param[in] const TransformComponent& transform The transform component to be set to.
		*/
		void SetCameraTransform(const TransformComponent& transform) { m_CameraTransform = transform; isChanged = true; }

		/*!
		* @brief Setter for the camera zoom speed.
		* 
		* @param[in] float speed The speed to set the camera zoom speed to.
		*/
		void SetCameraZoomSpeed(float speed) { m_cameraZoomSpeed = speed; }

		/*!
		* @brief Toggle to enable or disable camera rotation.
		* 
		* @param[in] bool enable Whether or not to enable camera rotation.
		*/
		void ToggleRotation(bool enable) { m_EnableRotation = enable; }

		/*!
		* @brief Setter for the max and min zoom levels.
		* 
		* @param[in] float zoom The zoom level to set the max and min zoom levels to.
		*/
		void SetMaxZoom(float zoom) { m_MaxZoom = zoom; }

		/*!
		* @brief Setter for the max and min zoom levels.
		* 
		* @param[in] float zoom The zoom level to set the max and min zoom levels to.
		*/
		void SetMinZoom(float zoom) { m_MinZoom = zoom; }

		/*!
		* @brief Getter for the camera zoom speed. Returns a reference to the camera zoom speed so that it can be changed.
		* 
		* @return float& The camera zoom speed.
		*/
		float& GetCameraZoomSpeed() { return m_cameraZoomSpeed; }

		/*!
		* @brief getter for the current current ability to zoom. Returns a reference so that it can be changed.
		* 
		* @return bool& The current ability to zoom.
		*/
		bool& GetRotationEnabled() { return m_EnableRotation; }

		/*!
		* @brief Getter for the max zoom level. Returns a reference so that they can be changed.
		* 
		* @return float& The max zoom level.
		*/
		float& GetMaxZoom() { return m_MaxZoom; }

		/*!
		* @brief Getter for the min zoom level. Returns a reference so that they can be changed.
		* 
		* @return float& The min zoom level.
		*/
		float& GetMinZoom() { return m_MinZoom; }

	private:
		/*!
		* @brief Function that is called when mouse is scrolled this modifies the zoom level by zooming in and out.
		* 
		* @details The function modifies the zoom level by zooming in and out. The zoom level is modified by the mouse scroll value multiplied by the camera zoom speed. The zoom level is then clamped between m_MinZoom and m_MaxZoom. Then the projection matrix is updated.
		* 
		* @see MouseScrolledEvent
		* @see OrthographicCameraController::SetZoom
		* 
		* @param[in] MouseScrolledEvent& e The mouse scrolled event that is triggered.
		*/
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		/*!
		* @brief Function that is called when the window is resized. This function updates the aspect ratio of the window and updates the projection matrix.
		* 
		* @see WindowResizeEvent
		* 
		* @param[in] WindowResizeEvent& e The window resize event that is triggered.
		*/
		bool OnWindowResizedEvent(WindowResizeEvent& e);

		/*!
		* @brief Function that is called when a mouse button is pressed.
		* 
		* @details The function checks if the middle mouse button is pressed and if it is it sets the m_canMoveMiddleMouse boolean to true and sets the m_InitialMousePosition to the current mouse position and the m_InitialCameraPosition to the current camera position. If the middle mouse button is not pressed the function returns false.
		* 
		* @see MouseButtonPressedEvent
		* 
		* @param[in] MouseButtonPressedEvent& e The mouse button pressed event that is triggered.
		*/
		bool OnMouseButtonDownEvent(MouseButtonPressedEvent& e);

		/*!
		* @brief Function that is called when a mouse button is released.
		* 
		* @details The function checks if the middle mouse button is released and if it is it sets the m_canMoveMiddleMouse boolean to false. If the middle mouse button is not released the function returns false.
		* 
		* @see MouseButtonReleasedEvent
		* 
		* @param[in] MouseButtonReleasedEvent& e The mouse button released event that is triggered.
		*/
		bool OnMouseButtonUpEvent(MouseButtonReleasedEvent& e);
	private:
		Utils::Timestep m_LastFrameTime; /// The delta time stored from the last frame to be used to smooth out the camera movement

		float m_AspectRatio; /// The current aspect ratio of the camera frustum
		float m_ZoomLevel = 1.0f; /// The current zoom level of the camera
		bool m_EnableRotation; /// Whether or not the camera can rotate
		TransformComponent m_CameraTransform; /// The transform component of the camera

		OrthographicCamera m_Camera; /// The orthographic camera

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f }; /// The initial mouse position when the middle mouse button is pressed
		glm::vec3 m_InitialCameraPosition = { 0.0f, 0.0f, 0.0f }; /// The initial camera position when the middle mouse button is pressed

		float m_MiddleMouseScale = 0.005f; /// The scale of the middle mouse movement
		float m_cameraTranslationSpeed = 1.0f; /// The speed of the camera translation
		float m_cameraRotationSpeed = 1.0f; /// The speed of the camera rotation
		float m_cameraZoomSpeed = 40.0f; /// The speed of the camera zoom
		float m_MaxZoom = 100.0f; /// The max zoom level of the camera
		float m_MinZoom = 0.25f; /// The min zoom level of the camera

		bool isChanged = true; /// Boolean to check if the camera has changed
		bool m_canMoveMiddleMouse = false; /// Boolean to check if the camera can move with the middle mouse button
	};

}