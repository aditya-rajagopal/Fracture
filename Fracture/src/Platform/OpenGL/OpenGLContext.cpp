#include "frpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Fracture
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
		m_WindowHandle(windowHandle)
	{
		FR_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle); // set current context to this window. This means that all future OpenGL calls will affect this window and its context.
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // load all OpenGL function pointers with GLAD. This is done after we've created a valid OpenGL context, which we do with glfwMakeContextCurrent.
		FR_CORE_ASSERT(status, "Failed to initialize"); // gladLoadGLLoader returns 0 if something went wrong during the loading process.

		FR_CORE_INFO("OpenGL Version: {0}, ", (const char*)glGetString(GL_VERSION));
		FR_CORE_INFO("Vendor: {0}, ", (const char*)glGetString(GL_VENDOR));
		FR_CORE_INFO("Renderer: {0}, ", (const char*)glGetString(GL_RENDERER));

		#ifdef FR_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			FR_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Fracture requires at least OpenGL version 4.5!");
		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		FR_PROFILE_SCOPE("OpenGLContext::SwapBuffers");
		glfwSwapBuffers(m_WindowHandle);
	}

}