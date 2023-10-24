#pragma once

#include "Event.h"


namespace Fracture {

	class FRACTURE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) // Constructor
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; } // Getter for the x position of the mouse
		inline float GetY() const { return m_MouseY; } // Getter for the y position of the mouse

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: Position (" << m_MouseX << ", " << m_MouseY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY; // The position of the mouse
	};

	class FRACTURE_API MouseScrolledEvent : public Event
	{
	public:
		// The offset of the mouse scroll is the distance the mouse wheel has moved in the x and y direction
		// we also consider the case where the mouse wheel is moved horizontally
		MouseScrolledEvent(float xOffset, float yOffset) // Constructor
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; } // Getter for the x offset of the mouse
		inline float GetYOffset() const { return m_YOffset; } // Getter for the y offset of the mouse

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: Offset(" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset; // The offset of the mouse scroll
	};

	class FRACTURE_API MouseButtonEvent : public Event
	{
	// Similar to KeyEvent, we have a base class for mouse button events and then we have child classes for the specific events
	public:
		inline int GetMouseButton() const { return m_Button; } // Getter for the mouse button
		inline int GetMouseMod() const { return m_Mods; } // Getter for the mods

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button, int mods) // Constructor
			: m_Button(button), m_Mods(mods) {}
		int m_Button; // The mouse button
		int m_Mods;
	};

	class FRACTURE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, int mods) // Constructor
			: MouseButtonEvent(button, mods) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class FRACTURE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button, int mods) // Constructor
			: MouseButtonEvent(button, mods) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}