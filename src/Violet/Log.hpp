#ifndef __VIOLET_LOGGER_H_
#define __VIOLET_LOGGER_H_

#include <memory>

#include "Core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Violet{
    class Log{
        public:
            static void init();
            inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger;}
            inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger;}

        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// core log macros
#define VGE_CORE_ERROR(...) Violet::Log::getCoreLogger()->error(__VA_ARGS__);
#define VGE_CORE_WARN(...) Violet::Log::getCoreLogger()->warn(__VA_ARGS__);
#define VGE_CORE_INFO(...) Violet::Log::getCoreLogger()->info(__VA_ARGS__);
#define VGE_CORE_TRACE(...) Violet::Log::getCoreLogger()->trace(__VA_ARGS__);

// client log macros
#define VGE_ERROR(...) Violet::Log::getClientLogger()->error(__VA_ARGS__);
#define VGE_WARN(...) Violet::Log::getClientLogger()->warn(__VA_ARGS__);
#define VGE_INFO(...) Violet::Log::getClientLogger()->info(__VA_ARGS__);
#define VGE_TRACE(...) Violet::Log::getClientLogger()->trace(__VA_ARGS__);

#endif // __LOG_H_
