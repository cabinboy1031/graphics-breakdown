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


#endif // __LOG_H_
