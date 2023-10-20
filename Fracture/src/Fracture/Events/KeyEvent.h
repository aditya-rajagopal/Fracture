#pragma once

#include "Event.h"


namespace Fracture {

	class FRACTURE_API KeyEvent : public Event
	{
	public: 
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput) // KeyEvent is both a keyboard event and an input event
	protected: // Protected so that only the child classes can access the keycode
		KeyEvent(int KeyCode) // Constructor is protected so that only the child classes can create an instance of the class
			: m_KeyCode(KeyCode) {}
		int m_keyCode; // We store the key code of the key that was pressed
	};

	class FRACTURE_API KeyPressedEvent : public KeyEvent
	{
	// When we press a key a signal will be sent. If we keep it pressed after a certain amount of time the signal will be sent again and this is the repeat.
	public:
		KeyPressedEvent(int keyCode, int repeatCount) // Constructor
			: keyEvent(keyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_repeatCount; } // Getter for the repeat count

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		
		EVENT_CLASS_TYPE(KeyPressed) // This macro is defined in Event.h and it overrides the virtual functions in the base class to return the type of the event and the name of the event.
	private:
		int m_repeatCount; // The number of times the key was pressed
	};

	class FRACTURE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) // Constructor
			: KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode;
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}