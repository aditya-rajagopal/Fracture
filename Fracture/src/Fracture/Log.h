#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Fracture {
	class FRACTURE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

// Internal engine logging macros
// the ::Fracture:: ensures it is accessed from the global namespace
#define FR_CORE_FATAL(...)	::Fracture::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define FR_CORE_ERROR(...)	::Fracture::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FR_CORE_WARN(...)	::Fracture::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FR_CORE_INFO(...)	::Fracture::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FR_CORE_TRACE(...)	::Fracture::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client logging macros
#define FR_FATAL(...)		::Fracture::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define FR_ERROR(...)		::Fracture::Log::GetClientLogger()->error(__VA_ARGS__)
#define FR_WARN(...)		::Fracture::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FR_INFO(...)		::Fracture::Log::GetClientLogger()->info(__VA_ARGS__)
#define FR_TRACE(...)		::Fracture::Log::GetClientLogger()->trace(__VA_ARGS__)
