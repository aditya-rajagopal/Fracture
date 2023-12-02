#pragma once
/*!
* @file WindowsInput.h
* 
* @brief Contains the Windows implementation of the Input class
* 
* @see Input
* 
* @author Aditya Rajagopal
*/
#include "Fracture\Input\Input.h"

namespace Fracture {

	/*!
	* @brief The Windows implementation of the Input class
	*/
	class WindowsInput : public Input
	{
	protected:
		/*!
		* @brief Implementation of the KeyPressed polling function
		* 
		* @details uses glfwGetKey to poll the key
		* 
		* @param[in] int keyCode: The key code of the key that is being polled
		* 
		* @return bool: True if the key is pressed, false otherwise
		*/
		virtual bool IsKeyPressedImpl(int keyCode) override;

		/*!
		* @brief Implementation of the MouseButtonPressed polling function
		* 
		* @details uses glfwGetMouseButton to poll the mouse button
		* 
		* @param[in] int button: The mouse button code of the mouse button that is being polled
		* 
		* @return bool: True if the mouse button is pressed, false otherwise
		*/
		virtual bool IsMouseButtonPressedImpl(int button) override;

		/*!
		* @brief Implementation of the GetMouseX polling function
		* 
		* @details uses GetMousePositionImpl to get the x position and maintain the same code path.
		* 
		* @return float: The x coordinate of the mouse cursor
		*/
		virtual float GetMouseXImpl() override;

		/*!
		* @brief Implementation of the GetMouseY polling function
		*
		* @details uses GetMousePositionImpl to get the x position and maintain the same code path.
		*
		* @return float: The y coordinate of the mouse cursor
		*/
		virtual float GetMouseYImpl() override;

		/*!
		* @brief Implementation of the GetMousePosition polling function
		* 
		* @details uses glfwGetCursorPos to get the mouse position
		* 
		* @return std::pair<float, float>: The x and y coordinates of the mouse cursor
		*/
		virtual std::pair<float, float> GetMousePositionImpl() override;
	};

}