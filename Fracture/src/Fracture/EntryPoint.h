#pragma once


#ifdef FR_PLATFORM_WINDOWS

extern Fracture::Application* Fracture::CreateApplication();

void main(int argc, char** argv)
{
	auto app = Fracture::CreateApplication();
	app->Run();
	delete app;
}

#endif