#pragma once
#include "frpch.h"
#include "Fracture\Core\Core.h"


namespace Fracture {

	//TODO: Buffer events and process during update stage in an events pass

	enum class EventType
	{
		// These are implemented in the individual event classes
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};

// Here ## is the token pasting operator (https://en.cppreference.com/w/cpp/preprocessor/replace) 
// This is the override of the virtual function in the base class
// We get the string representation of the type of the event class (e.g. "WindowResize")
// We need a GetStaticType() to get what type of event it is in a polymorphic way (e.g. to check if it is a KeyPressedEvent)
// In dispatching the events we will use the GetStaticType() to check what type of event an incoming event is and check if it is the same as the type of the event we are trying to dispatch
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class FRACTURE_API Event
	{
		friend class EventDispatcher; // The event dispatcher can access the protected members of the event class
	public:
		virtual EventType GetEventType() const = 0; // Pure Virtual function, to gethe type of the event
		virtual const char* GetName() const = 0; // Pure Virtual function, to get the name of the event
		virtual int GetCategoryFlags() const = 0; // Pure Virtual function, to get the category flags of the event in bit mask form
		virtual std::string ToString() const { return GetName(); } // Virtual function, typecast the const char* GetName() to a string

		inline bool IsInCategory(EventCategory category) // Check if the event is in a certain category
		{
			return GetCategoryFlags() & category; // This is a bitwise AND operation. It checks if the category is in the flags of the event
		}

		bool Handled = false; // This is set to true if the event is handled by the event dispatcher
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : mEvent(event) {} // Constructor

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (mEvent.GetEventType() == T::GetStaticType())
			{
				// We convert the mEvent reference to a pointer of type T with (T*) and then dereference it with *
				// since we have defined EventFn<T> as function that takes a reference of event of type T and returns a bool
				mEvent.Handled = func(static_cast<T&>(mEvent)); // Call the function and cast the event to type T
				return true; // Return true if the event is of type T
			}
			return false; // Return false if the event is not of type T
		}
	private: 
		Event& mEvent; // Reference to the event that is being dispatched
	};

	inline std::ostream& operator<<(std::ostream& stream, const Event& event) // This is an overload of the << operator for events
	{
		return stream << event.ToString(); // This calls the ToString() function of the event
	}

}