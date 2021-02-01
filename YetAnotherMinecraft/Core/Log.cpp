#include "Log.h"

namespace REngine {
    std::shared_ptr<spdlog::logger> Log::clientLogger;
    std::shared_ptr<spdlog::logger> Log::coreLogger;

    void Log::init() {
        if (!isInitialized) {
            spdlog::set_pattern("%^[%T] %n: %v%$");
            coreLogger = spdlog::stdout_color_mt("REngine");
            coreLogger->set_level(spdlog::level::trace);
            clientLogger = spdlog::stderr_color_mt("APP");
            clientLogger->set_level(spdlog::level::trace);
            isInitialized = true;
        }
        else {
            R_CORE_WARN("Logging system was already initialized!");
        }
    }

    bool Log::isInitialized = false;
}