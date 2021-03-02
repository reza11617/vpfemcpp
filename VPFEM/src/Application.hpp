#pragma once

#include "Core.hpp"
#include "Log.hpp"
#include "FiniteElementModel.hpp"
#include "src/Analyze/Solver.hpp"

namespace VPFEM {
    class Application
    {
        public:
            Application();
            virtual ~Application();
            void Run();

            template<typename T, typename ... Ts>
            void PushFiniteElementModel(Ts ... args)
            {
                m_v_fem.emplace_back(std::make_shared<T>(args...));
                total_fem_number++;
                m_v_fem.back()->SetFiniteElementModelNumber(total_fem_number);
                std::string recorder_dir = m_path + "/Model_" + std::to_string(total_fem_number);
                m_v_fem.back()->SetRecorderDir(recorder_dir);
            }
            static std::string CreateDirectory(const std::string& path, size_t file_number);
        private:
            std::vector<std::future<void>> m_future;
            std::vector<std::shared_ptr<FiniteElementModel>> m_v_fem;
            size_t total_fem_number = 0;
            std::string m_path;
    };

    // To be defined in CLIENT code
    Application* CreateApplication();
}
