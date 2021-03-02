#include "Application.hpp"

namespace VPFEM {
    Application::Application()
    {
        VP_PROFILE_FUNCTION();
        m_path = CreateDirectory("Results/FEM", 0);

    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
#define ASYNC 1
#if ASYNC
        for (auto fem: m_v_fem)
            m_future.push_back(std::async(std::launch::async, Solver::ElasticAnalysis, fem));
#else
        for (auto fem: m_v_fem)
        {
            Solver::ElasticAnalysis(fem);
        }
#endif
    }



    std::string Application::CreateDirectory(const std::string& path, size_t file_number)
    {
        std::string local_path = path + "_" + std::to_string(file_number);
        if (std::filesystem::create_directories(local_path))
        {
            VP_CORE_INFO("{0} created", local_path);
            return local_path;
        } else
        {
            VP_CORE_INFO("{0} existed", local_path);
            file_number++;
            return Application::CreateDirectory(path, file_number);
        }
    }
}
