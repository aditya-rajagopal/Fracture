#pragma once
/*
* @file Event.h
* @brief Event header file containing the Event class and the EventDispatcher class.
* 
* @see ApplicationEvent.h
* @see KeyEvent.h
* @see MouseEvent.h
* 
* @author Aditya Rajagopal
*/

#include "frpch.h"
#include "Fracture\Core\Core.h"


namespace Fracture {

	//TODO: Buffer events and process during update stage in an events pass

	/*!
	* @brief Enum class for the different types of events.
	*/
	enum class EventType
	{
		// These are implemented in the individual event classes
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/*!
	* @brief Enum class for the different categories of events. These are bit masks that can be combined
	*/
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

/// Macro that overrides the virtual function in the base class to return the category flags of the event
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/*!
	* @brief Base class for all events.
	*/
	class FRACTURE_API Event
	{
		friend class EventDispatcher; // The event dispatcher can access the protected members of the event class
	public:
		/*!
		* @brief Pure Virtual function, to get the type of the event
		* 
		* @see EventType
		* 
		* @return EventType The type of the event
		*/
		virtual EventType GetEventType() const = 0; // 

		/*!
		* @brief Pure Virtual function, to get the name of the event
		* 
		* @return const char* The name of the event
		*/
		virtual const char* GetName() const = 0;

		/*!
		* @brief Pure Virtual function, to get the category flags of the event
		* 
		* @return int The category flags of the event
		*/
		virtual int GetCategoryFlags() const = 0;

		/*!
		* @brief Virtual function, to get the string representation of the event. Default implementation is to return the name of the event.
		* 
		* @return std::string The string representation of the event
		*/
		virtual std::string ToString() const { return GetName(); }

		/*!
		* @brief Function to check if the event is in a certain category
		* 
		* @param EventCategory category: The category to check
		*/
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category; // This is a bitwise AND operation. It checks if the category is in the flags of the event
		}

		bool Handled = false; /// This is set to true if the event is handled by the event dispatcher
	};

	class EventDispatcher
	{
	public:
		/*!
		* @brief Constructor for the event dispatcher.
		* 
		* @param Event& event: The event that is being dispatched
		*/
		EventDispatcher(Event& event) : mEvent(event) {}

		/*!
		* @brief Dispatch function that takes a function as a parameter and calls it if the event is of type T
		* 
		* @tparam T: The type of the event
		* @tparam F: The type of the function
		* 
		* @param const F& func: The function that is being to be called. It takes a reference of type T and returns a bool
		* 
		* @return bool: Returns true if the event is of type T
		*/
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
		Event& mEvent; /// Reference to the event that is being dispatched
	};

	/*!
	* @brief Overload of the << operator for events. It calls the ToString() function of the event and then pushes it to the stream.
	* 
	* @param std::ostream& stream: The stream to push the event to
	* @param const Event& event: The event to push to the stream
	* 
	* @return std::ostream&: The stream with the event pushed to it
	*/
	inline std::ostream& operator<<(std::ostream& stream, const Event& event)
	{
		return stream << event.ToString(); // This calls the ToString() function of the event
	}

}