#pragma once

#include "frpch.h"

#include "Fracture\Core\Core.h"
#include "Fracture\Events\Event.h"

namespace Fracture {

	struct WindowProperties
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(const std::string& title = "Fracture Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			:Title(title), Width(width), Height(height)
		{
		}
	};

	// Window interface representing a desktop system based Window
	class FRACTURE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
		

		// The reason we return a void pointer is this could technically be any window not necessarily a GLFW window.
		virtual void* GetNativeWindow() const = 0; // this is a function that will return a void pointer to the window object. This is used to get the window object from anywhere in the program.
	};

}

