#pragma once

extern VPFEM::Application* VPFEM::CreateApplication();

int main(int argc, char** argv)
{
    VPFEM::Log::Init();
    auto app = VPFEM::CreateApplication();
    app->Run();
    delete app;
}
