#pragma once

#include "Core.hpp"
#include "Log.hpp"
#include "src/Geometry/Model.hpp"
#include "src/Geometry/Node.hpp"

namespace VPFEM {
    class Application
    {
    public:
        Application();
        ~Application();
        void Run();
    private:
        
    };

    // To be defined in CLIENT code
    Application* CreateApplication();
}
