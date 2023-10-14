#pragma once


#ifdef FR_PLATFORM_WINDOWS

extern Fracture::Application* Fracture::CreateApplication();

void main(int argc, char** argv)
{
	Fracture::Log::Init();
	FR_CORE_TRACE("Initialized Fracture Log!");
	FR_CORE_WARN("Initialized Fracture Log!");
	FR_WARN("Initialized Game Log with macros!");

	auto app = Fracture::CreateApplication();
	app->Run();
	delete app;
}

#endif