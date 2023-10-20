#pragma once

#include "Event.h"


namespace Fracture {

	class FRACTURE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) // Constructor
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; } // Getter for the width of the window
		inline unsigned int GetHeight() const { return m_Height; } // Getter for the height of the window

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: W:" << m_Width << ", H:" << m_Height;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)
	private:
		unsigned int m_Width, m_Height; // The width and height of the window
	};


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