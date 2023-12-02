#pragma once
/*!
* @file Event.h
* @brief Contains classes for storing Keyboard events
* 
* @see Event
* 
* @author Aditya Rajagopal
*/

#include "Event.h"


namespace Fracture {

	/*!
	* @brief the base class for KeyEvents
	* 
	* @see Event
	*/
	class FRACTURE_API KeyEvent : public Event
	{
	public:
		/*!
		* @brief return the key code of the key that was pressed
		* 
		* @return int the key code of the key that was pressed
		*/
		inline int GetKeyCode() const { return m_KeyCode; }

		/*!
		* @brief return the mods of the key that was pressed
		* 
		* @return int the mods of the key that was pressed
		*/
		inline int GetKeyMods() const { return m_Mods; }

		/*
		* @brief KeyEvent is both a keyboard event and an input event
		*/
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected: // Protected so that only the child classes can access the keycode
		/*!
		* @breif Protected constructor so that only the child classes can create an instance of this class
		* 
		* @param[in] int keyCode the key code of the key that was pressed
		* @param[in] int mods the mods of the key that was pressed
		*/
		KeyEvent(int keyCode, int mods) 
			: m_KeyCode(keyCode), m_Mods(mods) {}
		int m_KeyCode; /// Stores the key code of the key that was pressed
		int m_Mods; /// Stores the mods of the key that was pressed
	};

	/*!
	* @brief Event class for when a key is pressed
	* 
	* @see KeyEvent
	* @see Event
	*/
	class FRACTURE_API KeyPressedEvent : public KeyEvent
	{
	public:
		/*!
		* @brief Constructor for the KeyPressedEvent
		* 
		* @details When we press a key a signal will be sent. If we keep it pressed after a certain amount of time the signal will be sent again and this is the repeat.
		* 
		* @param[in] int keyCode the key code of the key that was pressed
		* @param[in] bool repeatCount the number of times the key was pressed
		*/
		KeyPressedEvent(int keyCode, bool repeatCount, int mods)
			: KeyEvent(keyCode, mods), m_IsRepeated(repeatCount) {}

		/*!
		* @brief getter for checking if this is a repeated key press or the first time the key was pressed
		* 
		* @return bool true if the key was pressed more than once, false otherwise
		*/
		inline bool IsRepeated() const { return m_IsRepeated; }

		/*!
		* @brief returns a string representation of the event
		* 
		* @return std::string the string representation of the event
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << m_IsRepeated ? "(Repeated)" : "";
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyPressed) // This macro is defined in Event.h and it overrides the virtual functions in the base class to return the type of the event and the name of the event.
	private:
		bool m_IsRepeated; /// Boolean to check if the key was pressed more than once
	};


	/*!
	* @brief Event class for when a key is released
	* 
	* @see KeyEvent
	* @see Event
	*/
	class FRACTURE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		/*!
		* @brief Constructor for the KeyReleasedEvent
		* 
		* @param[in] int keyCode the key code of the key that was pressed
		* @param[in] int mods the mods of the key that was pressed
		*/
		KeyReleasedEvent(int keyCode, int mods) // Constructor
			: KeyEvent(keyCode, mods) {}

		/*!
		* @brief returns a string representation of the event
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	/*!
	* @brief Event class for when a key is typed
	* 
	* @see KeyEvent
	* @see Event
	*/
	class FRACTURE_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode) // Constructor
			: KeyEvent(keyCode, 0) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}