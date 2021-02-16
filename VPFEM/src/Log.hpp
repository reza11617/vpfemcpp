#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace VPFEM {
    class Log
    {
        public:
            static void Init();

            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;}
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;}

        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;


    };
}

// Core log macros
#define VP_CORE_TRACE(...)    ::VPFEM::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VP_CORE_INFO(...)     ::VPFEM::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VP_CORE_WARN(...)     ::VPFEM::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VP_CORE_ERROR(...)    ::VPFEM::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VP_CORE_CRITICAL(...) ::VPFEM::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define VP_TRACE(...)         ::VPFEM::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VP_INFO(...)          ::VPFEM::Log::GetClientLogger()->info(__VA_ARGS__)
#define VP_WARN(...)          ::VPFEM::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VP_ERROR(...)         ::VPFEM::Log::GetClientLogger()->error(__VA_ARGS__)
#define VP_CRITICAL(...)      ::VPFEM::Log::GetClientLogger()->critical(__VA_ARGS__)
