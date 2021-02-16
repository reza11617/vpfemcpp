#include <VPFEM>

#include "BeamElementExample.hpp"

class Sandbox : public VPFEM::Application
{
    private:
    public:
        Sandbox()
        {
            BeamElementExample *b1 = new BeamElementExample(1.0, 1.0, 3);
            delete b1;

            BeamElementExample *b2 = new BeamElementExample(1.0, 1.0, 2);
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
