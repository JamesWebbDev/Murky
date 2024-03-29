#include "mkpch.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Murky
{
	std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$"); // ('Timestamp' 'Logger Name' 'Error Name' 'Desc')
		s_EngineLogger = spdlog::stdout_color_mt("MURKY");
		s_EngineLogger->set_level(spdlog::level::trace);


		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}