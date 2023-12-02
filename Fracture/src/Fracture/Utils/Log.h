#pragma once
/*!
* @file Log.h
* @brief Contains the Log class that is used to log messages to the console.
* 
* @see spdlog
* 
* @todo: Add logging to file
* 
* @author Aditya Rajagopal
*/

#include "Fracture\Core\Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Fracture {

	/*!
	* @brief The Log class is used to log messages to the console.
	*/
	class FRACTURE_API Log
	{
	public:
		/*!
		* @brief Function that initializes the logging system. Sets  up the core logger and the client logger  with the appropriate formatting.
		*/
		static void Init();

		/*!
		* @brief Function that returns the core logger.
		* 
		* @return Ref<spdlog::logger>&: The core logger.
		*/
		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		/*!
		* @brief Function that returns the client logger.
		* 
		* @return Ref<spdlog::logger>&: The client logger.
		*/
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_ClientLogger; /// The client logger
		static Ref<spdlog::logger> s_CoreLogger; /// The core logger
	};
}

// Internal engine logging macros
// the ::Fracture:: ensures it is accessed from the global namespace
#define FR_CORE_CRITICAL(...)	::Fracture::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define FR_CORE_ERROR(...)		::Fracture::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FR_CORE_WARN(...)		::Fracture::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FR_CORE_INFO(...)		::Fracture::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FR_CORE_TRACE(...)		::Fracture::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client logging macros
#define FR_CRITICAL(...)		::Fracture::Log::GetClientLogger()->critical(__VA_ARGS__)
#define FR_ERROR(...)			::Fracture::Log::GetClientLogger()->error(__VA_ARGS__)
#define FR_WARN(...)			::Fracture::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FR_INFO(...)			::Fracture::Log::GetClientLogger()->info(__VA_ARGS__)
#define FR_TRACE(...)			::Fracture::Log::GetClientLogger()->trace(__VA_ARGS__)
