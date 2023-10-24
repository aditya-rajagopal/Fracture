#pragma once

#include "Event.h"


namespace Fracture {

	class FRACTURE_API KeyEvent : public Event
	{
	public: 
		inline int GetKeyCode() const { return m_KeyCode; }
		inline int GetKeyMods() const { return m_Mods; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput) // KeyEvent is both a keyboard event and an input event
	protected: // Protected so that only the child classes can access the keycode
		KeyEvent(int keyCode, int mods) // Constructor is protected so that only the child classes can create an instance of the class
			: m_KeyCode(keyCode), m_Mods(mods) {}
		int m_KeyCode; // We store the key code of the key that was pressed
		int m_Mods; // We store the mods of the key that was pressed
	};

	class FRACTURE_API KeyPressedEvent : public KeyEvent
	{
	// When we press a key a signal will be sent. If we keep it pressed after a certain amount of time the signal will be sent again and this is the repeat.
	public:
		KeyPressedEvent(int keyCode, bool repeatCount, int mods) // Constructor
			: KeyEvent(keyCode, mods), m_IsRepeated(repeatCount) {}

		inline bool IsRepeated() const { return m_IsRepeated; } // Getter for the repeat count

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << m_IsRepeated ? "(Repeated)" : "";
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyPressed) // This macro is defined in Event.h and it overrides the virtual functions in the base class to return the type of the event and the name of the event.
	private:
		bool m_IsRepeated; // The number of times the key was pressed
	};

	class FRACTURE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode, int mods) // Constructor
			: KeyEvent(keyCode, mods) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

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