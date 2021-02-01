#pragma once

#include "Core.hpp"

namespace VPFEM {
    class Application
    {
        public:
            Application();
            ~Application();
            void Run();
    };

    // To be defined in CLIENT code
    Application* CreateApplication();
}
