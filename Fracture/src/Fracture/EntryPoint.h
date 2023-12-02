#pragma once
/*! 
 * @file EntryPoint.h
 * @brief Contains the main function of the application. This is the entry point of the engine.
 * 
 * @see Application
 * 
 * @todo: Add support for other platforms.
 * 
 * @author: Aditya Rajagopal
 */

#ifdef FR_PLATFORM_WINDOWS

	extern Fracture::Application* Fracture::CreateApplication(); /// forward declaration of the CreateApplication function. This function is defined in the client application.

	/*!
	* @brief The main function of the engine. This is the entry point of the engine.
	* 
	* @details the CreateApplication function is called to create the application class. The application class is then run. The CreateApplication function is defined in the client application.
	* 
	* @see Application
	*/
	void main(int argc, char** argv)
	{
		FR_BEGIN_PROFILE_SESSION("Startup", "../Logs/FractureProfile-Startup.json");
		{
			FR_PROFILE_SCOPE("Log Init");
			Fracture::Log::Init();
		}
		FR_END_PROFILE_SESSION();
		FR_CORE_TRACE("Initialized Fracture Log!");
		FR_CORE_WARN("Initialized Fracture Log!");
		FR_WARN("Initialized Game Log with macros!");

		auto app = Fracture::CreateApplication();
		app->Run();
		delete app;
	}

#endif