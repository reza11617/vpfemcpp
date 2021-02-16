#pragma once

#include "Core.hpp"
#include "Log.hpp"

namespace VPFEM {
    class Application
    {
        public:
            Application();
            virtual ~Application();
            void Run();
    };

    // To be defined in CLIENT code
    Application* CreateApplication();
}
