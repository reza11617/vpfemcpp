#pragma once

extern VPFEM::Application* VPFEM::CreateApplication();

int main(int argc, char** argv)
{
    VPFEM::Log::Init();
    VP_PROFILE_BEGIN_SESSION("Startup", "VpfemProfile-Startup.json");
    auto app = VPFEM::CreateApplication();
    VP_PROFILE_END_SESSION();

    VP_PROFILE_BEGIN_SESSION("Runtime", "VpfemProfile-Runtime.json");
    app->Run();
    VP_PROFILE_END_SESSION();

    VP_PROFILE_BEGIN_SESSION("Shutdown", "VpfemProfile-Shotdown.json");
    delete app;
    VP_PROFILE_END_SESSION();
}
