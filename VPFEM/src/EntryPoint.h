#pragma once

extern VPFEM::Application* VPFEM::CreateApplication();

int main(int argc, char** argv)
{
    VPFEM::Log::Init();
    VP_CORE_WARN("Initialized Log!");
    VP_INFO("Initialized Log!");
    auto app = VPFEM::CreateApplication();
    app->Run();
    delete app;
}
