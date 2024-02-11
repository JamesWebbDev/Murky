#ifndef MK_LOG_H
#define MK_LOG_H

#include "core.h"
#include "spdlog/spdlog.h"

#include <memory>

namespace Murky
{
	class MURKY_API Log
	{
	private: 

		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	};
}

// Engine Log macros
#define MK_ENG_TRACE(...) ::Murky::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define MK_ENG_INFO(...)  ::Murky::Log::GetEngineLogger()->info (__VA_ARGS__)
#define MK_ENG_WARN(...)  ::Murky::Log::GetEngineLogger()->warn (__VA_ARGS__)
#define MK_ENG_ERROR(...) ::Murky::Log::GetEngineLogger()->error(__VA_ARGS__)
#define MK_ENG_FATAL(...) ::Murky::Log::GetEngineLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define MK_TRACE(...)     ::Murky::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MK_INFO(...)      ::Murky::Log::GetClientLogger()->info (__VA_ARGS__)
#define MK_WARN(...)      ::Murky::Log::GetClientLogger()->warn (__VA_ARGS__)
#define MK_ERROR(...)     ::Murky::Log::GetClientLogger()->error(__VA_ARGS__)
#define MK_FATAL(...)     ::Murky::Log::GetClientLogger()->fatal(__VA_ARGS__)


// if Dist 
// #define MK_INFO 

#endif