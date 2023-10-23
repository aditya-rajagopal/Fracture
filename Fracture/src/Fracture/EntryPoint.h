#pragma once


#ifdef FR_PLATFORM_WINDOWS

extern Fracture::Application* Fracture::CreateApplication();

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