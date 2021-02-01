#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace REngine {
    class Log {
    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;
        static bool isInitialized;
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }

        inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }
    };
}

//Core log macros
#define R_CORE_TRACE(...) ::REngine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define R_CORE_INFO(...)  ::REngine::Log::getCoreLogger()->info(__VA_ARGS__)
#define R_CORE_WARN(...)  ::REngine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define R_CORE_ERROR(...) ::REngine::Log::getCoreLogger()->error(__VA_ARGS__)
#define R_CORE_FATAL(...) ::REngine::Log::getCoreLogger()->fatal__VA_ARGS__)

//Client log macros
#define R_TRACE(...)      ::REngine::Log::getClientLogger()->trace(__VA_ARGS__)
#define R_INFO(...)       ::REngine::Log::getClientLogger()->info(__VA_ARGS__)
#define R_WARN(...)       ::REngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define R_ERROR(...)      ::REngine::Log::getClientLogger()->error(__VA_ARGS__)
#define R_FATAL(...)      ::REngine::Log::getClientLogger()->fatal__VA_ARGS__)