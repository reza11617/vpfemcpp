#include <VPFEM>
#include <future>
#include "BeamElementExample.hpp"

static std::mutex s_FErunner;
class Sandbox : public VPFEM::Application
{
    private:
        std::vector<std::future<void>> m_future;
    public:
        Sandbox()
        {
            std::vector<BeamElementExample*> beam;
            beam.push_back(new BeamElementExample(20.0,100,700,"CG"));
            beam.push_back(new BeamElementExample(20.0,100,700,"CG"));
            beam.push_back(new BeamElementExample(20.0,100,700,"CG"));
            beam.push_back(new BeamElementExample(20.0,100,700,"CG"));
            beam.push_back(new BeamElementExample(20.0,100,700,"CG"));
#define ASYNC 0
#if ASYNC
            for (auto b : beam)
                b->Run();
#else
            for (auto &b: beam)
                m_future.push_back(std::async(std::launch::async, FERuner, b));
#endif
        }

        static void FERuner(BeamElementExample* beam)
        {

            VP_PROFILE_FUNCTION();
            beam->Run();
            std::lock_guard<std::mutex> lock(s_FErunner);
        }

        ~Sandbox()
        {
        }
};

VPFEM::Application* VPFEM::CreateApplication()
{
    return new Sandbox();
}
