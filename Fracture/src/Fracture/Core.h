#pragma once


#ifdef FR_PLATFORM_WINDOWS
	#ifdef FR_BUILD_DLL
		#define FRACTURE_API __declspec(dllexport)
	#else
		#define FRACTURE_API __declspec(dllimport)
	#endif
#else
	#error Fracture only supports Windows!
#endif