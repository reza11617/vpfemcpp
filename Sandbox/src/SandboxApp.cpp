#include <VPFEM>

class Sandbox : public VPFEM::Application
{
public:
    Sandbox()
    {

    }
    ~Sandbox()
    {

    }
};

VPFEM::Application* VPFEM::CreateApplication()
{
    return new Sandbox;
}
