#pragma once
/**
* @file Core.h
* @brief Core header file.
* 
* Contains the core macros and functions to be used throughout the engine.
* 
* @author Aditya Rajagopal
*/


#include <memory>

#ifdef FR_PLATFORM_WINDOWS
	#ifdef FR_DYNAMIC_LINK
		#ifdef FR_BUILD_DLL
			#define FRACTURE_API __declspec(dllexport)
		#else
			#define FRACTURE_API __declspec(dllimport)
		#endif
	#else
		#define FRACTURE_API
	#endif
#else
	#error Fracture only supports Windows!
#endif

#ifdef FR_DEBUG
	#define FR_ENABLE_ASSERTS
#endif

#ifdef FR_ENABLE_ASSERTS
	#define FR_ASSERT(x, ...) { if(!(x)) { FR_ERROR("Assertion Failed: "); FR_ERROR(__VA_ARGS__); __debugbreak(); } }
	#define FR_CORE_ASSERT(x, ...) { if(!(x)) { FR_CORE_ERROR("Assertion Failed: "); FR_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
#else	
	#define FR_ASSERT(x, ...)
	#define FR_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x) // This is a bit shift operator. It shifts the bit 1 to the left x times. So BIT(0) = 00000001, BIT(1) = 00000010, BIT(2) = 00000100, etc.

#define FRACTURE_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Fracture{
	
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}