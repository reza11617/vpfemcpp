#include <VPFEM>
#include "BeamElementExample.hpp"

class Sandbox : public VPFEM::Application
{
    public:
        Sandbox()
        {
            for (size_t i = 0; i < 1; i++)
                PushFiniteElementModel<BeamElementExample>(20,100, 2000);
        }

        ~Sandbox()
        {
        }
};

VPFEM::Application* VPFEM::CreateApplication()
{
    return new Sandbox();
}
