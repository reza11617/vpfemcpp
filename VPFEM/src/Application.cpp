#include "Application.hpp"

namespace VPFEM {
    Application::Application()
    {
        VP_PROFILE_FUNCTION();
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
#define ASYNC 1
#if ASYNC
        for (auto fem: m_v_fem)
            m_future.push_back(std::async(std::launch::async, Solver::CGP, fem));

        for (size_t i = 0; i < m_v_fem.size(); i++)
        {
            VectorXld def = m_future[i].get();
            m_v_fem[i]->SetDeformation(def);
        }
#else
        for (auto fem: m_v_fem)
            FiniteElementRunEach(fem);
#endif
    }
}
