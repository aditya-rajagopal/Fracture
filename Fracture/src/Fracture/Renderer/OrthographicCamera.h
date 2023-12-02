#pragma once
/*!
* @file OrthographicCamera.h
* @brief Contains the OrthographicCamera class that is provided by the Fracture engine. It is intended that other cameras will be created by the user.
* 
* @author Aditya Rajagopal
*/

#include <Fracture\Components\Component.h>
#include <glm\glm.hpp>

namespace Fracture {

	class OrthographicCamera
	{
	public:
		/*!
		* @brief Constructor for the OrthographicCamera class that takes in the left, right, bottom, and top values of the camera frustum.
		* 
		* @detials The near and far values are set to -1 and 1 respectively. The values set by the user are used to create the projection matrix. The view matrix is set to the identity matrix.
		* The 4 values also determine the units of the world space. For example, if the left and right values are set to -10 and 10 respectively, then the world space will be from -10 to 10 in the x direction.
		* 
		* @param[in] float left The left value of the camera frustum
		* @param[in] float right The right value of the camera frustum
		* @param[in] float bottom The bottom value of the camera frustum
		* @param[in] float top The top value of the camera frustum
		*/
		OrthographicCamera(float left, float right, float bottom, float top);

		/*!
		* @brief Constructor for the OrthographicCamera class that takes in the left, right, bottom, top, near, and far values of the camera frustum.
		* 
		* @detials The values set by the user are used to create the projection matrix. The view matrix is set to the identity matrix. The 6 values also determine the units of the world space. For example, if the left and right values are set to -10 and 10 respectively, then the world space will be from -10 to 10 in the x direction.
		* 
		* @param[in] float left The left value of the camera frustum
		* @param[in] float right The right value of the camera frustum
		* @param[in] float bottom The bottom value of the camera frustum
		* @param[in] float top The top value of the camera frustum
		* @param[in] float nearval The near value of the camera frustum
		* @param[in] float farval The far value of the camera frustum
		*/
		OrthographicCamera(float left, float right, float bottom, float top, float nearval, float farval);

		/*!
		* @brief Destructor for the OrthographicCamera class.
		*/
		~OrthographicCamera();

		/*!
		* @brief Function that sets the projection matrix of the camera with the left, right, bottom, and top values of the camera frustum.
		* 
		* @detials The near and far values are set to -1 and 1 respectively. The values set by the user are used to create the projection matrix.
		*/
		void SetProjection(float left, float right, float bottom, float top, float nearval = -1, float farval = 1);
		
		/*!
		* @brief Getter for the projection matrix of the camera.
		* 
		* @return const glm::mat4& The projection matrix of the camera.
		*/
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

		/*!
		* @brief Getter for the view matrix of the camera.
		* 
		* @return const glm::mat4& The view matrix of the camera.
		*/
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }

		/*!
		* @brief Getter for the view projection matrix of the camera.
		* 
		* @return const glm::mat4& The view projection matrix of the camera.
		*/
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

		/*!
		* @brief Setter for the projection matrix of the camera. Recalculates the view projection matrix.
		* 
		* @param[in] const glm::mat4& projection The projection matrix of the camera.
		*/
		void SetProjectionMatrix(const glm::mat4& projection) { m_ProjectionMatrix = projection; m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }

		/*!
		* @brief Setter for the view matrix of the camera. Recalculates the view projection matrix.
		* 
		* @param[in] const glm::mat4& view The view matrix of the camera.
		*/
		void SetViewMatrix(const glm::mat4& view) { m_ViewMatrix = view; m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }
	private:
		glm::mat4 m_ProjectionMatrix; /// 4x4 projection matrix of the camera
		glm::mat4 m_ViewMatrix; /// 4x4 view matrix of the camera
		glm::mat4 m_ViewProjectionMatrix; /// 4x4 view projection matrix of the camera = projection * view
	};

}

