#pragma once
/*!
* @file Input.h
* @brief Input header file conatins the singleton class that will be implemented per platform to handle polling inputs.
* 
* @see WindowsInput
* @see KeyCodes.h
* @see MouseButtonCodes.h
* 
* @author Aditya Rajagopal
*/

#include "Fracture\Core\Core.h"

namespace Fracture {

	/*!
	* @brief The base class for Input polling. This class will be implemented per platform.
	* 
	* @details This class will be implemented per platform. This is a singleton class.
	* 
	* @see WindowsInput
	*/
	class FRACTURE_API Input
	{
	protected:
		/*!
		* @brief protected constructor so that only the child classes can create an instance of this class.
		*/
		Input() = default;
	public:
		/*!
		* @brief Deleted copy constructor so that we can not copy this class since it is a singleton
		*/
		Input(const Input&) = delete;

		/*!
		* @brief Deleted assignment operator so that we can not copy this class since it is a singleton
		*/
		Input& operator=(const Input&) = delete;

		/*!
		* @brief Static function that returns if a key is pressed or not
		* 
		* @param[in] int keyCode the key code of the key that we want to check if it is pressed
		* 
		* @return bool true if the key is pressed, false otherwise
		*/
		inline static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }

		/*!
		* @brief Static function that returns if a mouse button is pressed or not
		* 
		* @param[in] int button the mouse button code of the mouse button that we want to check if it is pressed
		* 
		* @return bool true if the mouse button is pressed, false otherwise
		*/
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		/*!
		* @brief Static function that returns the current x coordinate of the mouse
		* 
		* @return float the current x coordinate of the mouse
		*/
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }

		/*!
		* @brief Static function that returns the current y coordinate of the mouse
		* 
		* @return float the current y coordinate of the mouse
		*/
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		/*!
		* @brief Static function that returns the current x and y coordinates of the mouse at once
		* 
		* @return std::pair<float, float> the current x and y coordinates of the mouse
		*/
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
	protected:
		// These are the backend pure virtual functions that will be implemented per platform.
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
	private:
		static Scope<Input> s_Instance;
	};

}