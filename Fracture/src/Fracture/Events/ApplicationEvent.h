#pragma once
/*!
* @file ApplicationEvent.h
* @brief ApplicationEvent header file containing event definitions for windows and application events.
* 
* @see Event
*
* @author Aditya Rajagopal
*/

#include "Event.h"


namespace Fracture {
	
	/*!
	* @brief Event class for holding information about window resize events.
	*/
	class FRACTURE_API WindowResizeEvent : public Event
	{
	public:
		/*!
		* @brief Constructor for WindowResizeEvent. Takes the new width and height of the window as parameters.
		* 
		* @param[in] uint32_t width: The new width of the window.
		* @param[in] uint32_t height: The new height of the window.
		*/
		WindowResizeEvent(unsigned int width, unsigned int height) // Constructor
			: m_Width(width), m_Height(height) {}

		/*!
		* @brief Getter for the new width of the window.
		* 
		* @return uint32_t The new width of the window.
		*/
		inline unsigned int GetWidth() const { return m_Width; }

		/*!
		* @brief Getter for the new height of the window.
		* 
		* @return uint32_t The new height of the window.
		*/
		inline unsigned int GetHeight() const { return m_Height; }


		/*!
		* @brief Converts the WindowResizeEvent data to a string to be serialized or for debugging purposes.
		* 
		* @return std::string The WindowResizeEvent data as a string.
		*/
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: W:" << m_Width << ", H:" << m_Height;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)
	private:
		unsigned int m_Width; /// The new width of the window
		unsigned int m_Height; /// The new height of the window
	};

	/*!
	* @brief Event class for holding information about window close events.
	*/
	class FRACTURE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {} // Constructor

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)
	};

	class FRACTURE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {} // Constructor

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppTick)
	};

	class FRACTURE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {} // Constructor

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppUpdate)
	};

	class FRACTURE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {} // Constructor

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppRender)
	};

}