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
        // Testing quad element delete after testing is done
        std::vector<std::shared_ptr<Node>> node;
        node.emplace_back(std::make_shared<Node>(0.0,0.0));
        node.emplace_back(std::make_shared<Node>(0.0,1.0));
        node.emplace_back(std::make_shared<Node>(1.0,1.0));
        node.emplace_back(std::make_shared<Node>(1.0,0.0));
        std::shared_ptr<Material> mat;
        mat = std::make_shared<ElasticPlainStress>(1000.0,0.3);
        Quad4 a(node[0],
                node[1],
                node[2],
                node[3],
                Quad4::Nip::Four,
                mat);
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
