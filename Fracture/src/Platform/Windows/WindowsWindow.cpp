#include "frpch.h"
#include "WindowsWindow.h"

#include "Fracture\Events\ApplicationEvent.h"
#include "Fracture\Events\KeyEvent.h"
#include "Fracture\Events\MouseEvent.h"

#include "Platform\OpenGL\OpenGLContext.h"


namespace Fracture {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		FR_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		FR_CORE_INFO("Creating window OpenGL: {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);


		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			FR_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init(); // initialize the graphics context. This will load all OpenGL function pointers via GLAD. We pass glfwGetProcAddress to gladLoadGLLoader to load the OpenGL function pointers that are unique to the current context (in this case the GLFW window we just created).

		// in glfw we can provide a pointer to some user-defined data with glfwSetWindowUserPointer. We can use this to store a pointer to our WindowData struct.
		// This can be later retrieved with glfwGetWindowUserPointer. This is useful for example when we want to access the window data from within a GLFW callback function.
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) // lambda function
			{
				// glfwGetWindowUserPointer returns a void* pointer to the user-defined data of this window. We set this pointer with glfwSetWindowUserPointer in the Init() method.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // get window data from user pointer
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // get window data from user pointer

				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // get window data from user pointer

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, false, mods);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key, mods);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, true, mods);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // get window data from user pointer

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button, mods);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button, mods);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // get window data from user pointer

				MouseMovedEvent event((float)xpos, (float)ypos);
				data.EventCallback(event);
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // get window data from user pointer

				MouseScrolledEvent event((float)xoffset, (float)yoffset);
				data.EventCallback(event);
			});
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		{
			FR_PROFILE_SCOPE("WindowsWindow::OnUpdate::glfwPollEvents");
			glfwPollEvents(); // checks if any events are triggered (like keyboard input or mouse movement events), updates the window state, and calls the corresponding functions (which we can set via callback methods)
		}
		m_Context->SwapBuffers(); // swap the color buffer (a large buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}


	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}
