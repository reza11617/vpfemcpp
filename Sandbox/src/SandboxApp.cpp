#include <VPFEM>
#include "BeamElementExample.hpp"

class Sandbox : public VPFEM::Application
{
    public:
        Sandbox()
        {
            PushFiniteElementModel<BeamElementExample>(20,100,700);
            PushFiniteElementModel<BeamElementExample>(20,100,700);
            PushFiniteElementModel<BeamElementExample>(20,100,700);
            PushFiniteElementModel<BeamElementExample>(20,100,700);
            PushFiniteElementModel<BeamElementExample>(20,100,700);
        }

        ~Sandbox()
        {
        }
};

VPFEM::Application* VPFEM::CreateApplication()
{
    return new Sandbox();
}
