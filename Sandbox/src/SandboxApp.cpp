#include <VPFEM>
#include "BeamElementExample.hpp"

class Sandbox : public VPFEM::Application
{
    public:
        Sandbox()
        {
            PushFiniteElementModel<BeamElementExample>(20,100,7);
            PushFiniteElementModel<BeamElementExample>(20,100,7);
            PushFiniteElementModel<BeamElementExample>(20,100,7);
            PushFiniteElementModel<BeamElementExample>(20,100,7);
            PushFiniteElementModel<BeamElementExample>(20,100,7);
        }

        ~Sandbox()
        {
        }
};

VPFEM::Application* VPFEM::CreateApplication()
{
    return new Sandbox();
}
