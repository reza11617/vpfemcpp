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
            m_future.push_back(std::async(std::launch::async, Solver::CG, fem));

        for (size_t i = 0; i < m_v_fem.size(); i++)
        {
            VectorXld def = m_future[i].get();
            m_v_fem[i]->SetDeformation(def);
        }
#else
        for (auto fem: m_v_fem)
            FiniteElementRunEach(fem);
#endif
        for (size_t i = 0; i < m_v_fem.size(); i++)
            VP_CORE_INFO("Model: {0}\tNode: {1}\tDeformation: {2}",
                         i,
                         m_v_fem[i]->GetNode().size()-1,
                         m_v_fem[i]->GetResult()->Deformation(m_v_fem[i]->GetNode().back(), 1));
    }
}
