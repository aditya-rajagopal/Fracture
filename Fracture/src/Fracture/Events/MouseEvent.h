#pragma once
/*!
* @file MouseEvent.h
* @brief Contains classes for storing Mouse events
* 
* @see Event
* 
* @author Aditya Rajagopal
*/


#include "Event.h"


namespace Fracture {

	/*!
	* @brief Event for when the mouse is moved
	* 	
	* @see Event
	*/
	class FRACTURE_API MouseMovedEvent : public Event
	{
	public:
		/*!
		* @brief Constructor for the MouseMovedEvent
		* 
		* @param x The x position of the mouse
		* @param y The y position of the mouse
		*/
		MouseMovedEvent(float x, float y) // Constructor
			: m_MouseX(x), m_MouseY(y) {}

		/*!
		* @brief Getter for the x position of the mouse
		* 
		* @return float x position of the mouse
		*/
		inline float GetX() const { return m_MouseX; }

		/*!
		* @brief Getter for the y position of the mouse
		* 
		* @return float y position of the mouse
		*/
		inline float GetY() const { return m_MouseY; }

		/*
		* @brief Serialise the event data to string
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: Position (" << m_MouseX << ", " << m_MouseY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		/*
		* @brief The category of the event is both mouse and 
		*/
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX; /* @brief x position of the event */
		float m_MouseY; /* @brief y position of the event */
	};

	/*!
	* @brief Event for when the mouse is scrolled
	* 
	* @see Event
	*/
	class FRACTURE_API MouseScrolledEvent : public Event
	{
	public:
		/*
		* @brief Constructor for the MouseScrolledEvent
		* 
		* @details The offset of the mouse scroll is the distance the mouse wheel has moved in the x and y direction. We also consider the case where the mouse wheel is moved horizontally
		* 
		* @param[in] float xOffset the offset of the mouse scroll in the x direction
		* @param[in] float yOffset the offset of the mouse scroll in the y direction
		*/
		MouseScrolledEvent(float xOffset, float yOffset) // Constructor
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		/*!
		* @brief Getter for the x offset of the mouse
		* 
		* @return float x offset of the mouse
		*/
		inline float GetXOffset() const { return m_XOffset; }

		/*!
		* @brief Getter for the y offset of the mouse
		*
		* @return float y offset of the mouse
		*/
		inline float GetYOffset() const { return m_YOffset; }

		/*!
		* @brief Serialise the event data to string
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: Offset(" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset; /// The X offset of the mouse scroll
		float m_YOffset; /// The Y offset of the mouse scroll
	};

	/*!
	* @brief Base class for mouse button events
	* 
	* @details Similar to KeyEvent, we have a base class for mouse button events and then we have child classes for the specific events
	* @see Event
	*/
	class FRACTURE_API MouseButtonEvent : public Event
	{
	public:
		/*!
		* @brief return the mouse code of the mouse button that was pressed
		*
		* @return int the mouse code of the mouse button that was pressed
		*/
		inline int GetMouseButton() const { return m_Button; }

		/*!
		* @brief return the mouse code of the mouse button that was pressed
		*
		* @return int the mouse code of the mouse button that was pressed
		*/
		inline int GetMouseMod() const { return m_Mods; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		/*!
		* @breif Protected constructor so that only the child classes can create an instance of this class
		*
		* @param[in] int button the code of the mouse button that was pressed
		* @param[in] int mods the mods of the mouse button that was pressed
		*/
		MouseButtonEvent(int button, int mods)
			: m_Button(button), m_Mods(mods) {}
		int m_Button; /// The mouse button code of the mouse button that was pressed
		int m_Mods; /// The mods pressed while the mouse button that was pressed
	};

	/*!
	* @brief Event class for when a mouse button is pressed
	* 
	* @see MouseButtonEvent
	* @see Event
	*/
	class FRACTURE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, int mods)
			: MouseButtonEvent(button, mods) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/*!
	* @brief Event class for when a mouse button is released
	*
	* @see MouseButtonEvent
	* @see Event
	*/
	class FRACTURE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button, int mods)
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