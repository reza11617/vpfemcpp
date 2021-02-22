#include <VPFEM>

#include "BeamElementExample.hpp"

class Sandbox : public VPFEM::Application
{
    private:
    public:
        Sandbox()
        {
            BeamElementExample *b1 = new BeamElementExample(20.0, 100.0, 200, "CG");
            delete b1;

            BeamElementExample *b2 = new BeamElementExample(20.0, 100.0, 200, "CGP");
            delete b2;
        }

        ~Sandbox()
        {

        }
};

VPFEM::Application* VPFEM::CreateApplication()
{
    return new Sandbox();
}
